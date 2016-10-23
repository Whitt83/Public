#include <vector>
#include <string>
#include <iostream>
#include <stddef.h>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <openssl/evp.h>
#include <cstring>


#include "csv_reader.hpp"
#include "data_file_format.hpp"
#include "base64.hpp"


static const std::string dataFilePath = "/home/wbatcheler/github/github-public/prj/destiny/data.csv";
static const size_t EXPECTED_FIELD_COUNT = 17;

void convertTextToRecords(CSVOutput_t const & csvResults, std::vector<DataRecord> & rawRecords);
void sanitizeRecords(std::vector<DataRecord> const & rawRecords, std::vector<DataRecord> & sanitizedRecords);
void checkChildCounts(std::vector<DataRecord> const & records, std::vector<DataRecord> & nodesWithSubOneChild);
void removeDuplicates(std::vector<DataRecord> const & sanitizedRecords, std::vector<DataRecord> & dedupedRecords);
void buildSize8Chains(std::vector<DataRecord> const & records, std::vector<std::vector<size_t> > & chains);
void decryptChains(std::vector<DataRecord> const & records, std::vector<std::vector<size_t> > const & chains);

int main(int argc, char ** argv)
{
    CSVOutput_t csvResults;
    bool const canLoadFile = loadCSVFile(dataFilePath, csvResults, true, ',');

    if (false == canLoadFile)
    {


    }

    std::cout << "Record Count:" << csvResults.size();


    std::vector<DataRecord> rawRecords;
    std::vector<DataRecord> sanitizedRecords;
    std::vector<DataRecord> dedupedRecords;
    convertTextToRecords(csvResults, rawRecords);
    sanitizeRecords(rawRecords, sanitizedRecords);
    std::cout << "Sanitized " << sanitizedRecords.size() << " for processing." << std::endl;
    removeDuplicates(sanitizedRecords, dedupedRecords);
    std::cout << "Deduped " << dedupedRecords.size() << " for processing." << std::endl;


    std::vector<DataRecord> nodesWithSubOneChild;
    checkChildCounts(dedupedRecords,nodesWithSubOneChild);

    /* These are references to indices in nodesWithSubOneChild */
    std::vector<std::vector<size_t> > chains;
    /* Find any chain of exactly 8 elements */
    buildSize8Chains(nodesWithSubOneChild, chains);

    /* try to decrypt them */
    decryptChains(nodesWithSubOneChild, chains);

}

void removeDuplicates(std::vector<DataRecord> const & sanitizedRecords, std::vector<DataRecord> & dedupedRecords)
{
    dedupedRecords.clear();
    for (std::vector<DataRecord>::const_iterator it = sanitizedRecords.begin(); it != sanitizedRecords.end(); ++it)
    {
        bool foundDupe = false;
        for (std::vector<DataRecord>::const_iterator it2 = dedupedRecords.begin(); it2 != dedupedRecords.end(); ++it2)
        {
            if (*it == *it2)
            {
                foundDupe = true;
            }
        }
        if (false == foundDupe)
        {
            dedupedRecords.push_back(*it);
        }
    }
}

void decryptChains(std::vector<DataRecord> const & records, std::vector<std::vector<size_t> > const & chains)
{
    for (std::vector<std::vector<size_t> >::const_iterator itChains = chains.begin(); itChains != chains.end(); itChains++)
    {
        std::stringstream ssIndices;
        std::stringstream ssKey;
        std::stringstream ssIV;
        std::stringstream ssEncryptedBytes;
        unsigned char binaryIV[16];
        unsigned char binaryKey[32];

        for (size_t i = 0; i < itChains->size(); i++)
        {
            size_t const index = itChains->at(i);
            ssIndices << std::setw(4) << std::setfill(' ') << index << " ";
            ssKey << base64_decode(records.at(index).processingKey_);
            std::string const strIV = base64_decode(records.at(index).iv_);
            ssEncryptedBytes << base64_decode(records.at(index).encryptedBytes_);
            std::vector<uint8_t> temporaryBinaryIV(16, 0);
            memcpy(&temporaryBinaryIV[0], &strIV[0], 16);
            for (size_t j = 0; j < 16; j++)
            {
                binaryIV[j] ^= temporaryBinaryIV[j];
            }
        }

        std::string const key = ssKey.str();
        unsigned char cstrKey[32];
        memcpy(cstrKey, &key[0], 32);

        //std::cout << ssIndices.str() << std::endl;

        std::string const encryptedBytes = ssEncryptedBytes.str();
        unsigned char ciphertext[32768];
        memcpy(ciphertext, &encryptedBytes[0], encryptedBytes.size());
        int ciphertextLength = 32768;
        /* Actual crypto part */
        EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
        int len;
        int plaintext_len;
        int const retval1 = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, cstrKey, binaryIV);
        //std::cout << "retval1: " << retval1 << std::endl;
        unsigned char plainText[32768];
        int plainTextLength = 32768;


        int const retval2 = EVP_DecryptUpdate(ctx, plainText, &plainTextLength, ciphertext, ciphertextLength);
        //std::cout << "retval2: " << retval2 << std::endl;
        for (size_t i = 0; i < 10; i++)
        {
            std::cout << std::hex << std::setw(2) << (int) plainText[i] << " " ;
        }
        std::cout << std::endl;

        //std::cout << std::string( (char *) &plainText[0], (size_t) plainTextLength) << std::endl;


    }

}
void checkChildCounts(std::vector<DataRecord> const & records, std::vector<DataRecord> & nodesWithSubOneChild)
{
    size_t multipleChildCount = 0;
    size_t singleChildCount = 0;
    size_t noChildrenCount = 0;
    for (size_t i = 0; i < records.size(); i++)
    {
        ChainNode newNode;
        newNode.index_ = i;
        /* Find all nodes whose original symbols match this node's mutated symbols */
        for (size_t j = 0; j < records.size(); j++)
        {
            if ( (records.at(i).mutatedSummary_ == records.at(j).originalSummary_) && (i != j) )
            {
                newNode.children_.push_back(j);
            }
        }
        if (newNode.children_.size() > 1)
        {
            multipleChildCount++;
        }
        if (newNode.children_.size() == 0)
        {
            noChildrenCount++;
            nodesWithSubOneChild.push_back(records.at(i));
        }
        if (newNode.children_.size() == 1)
        {
            singleChildCount++;
            nodesWithSubOneChild.push_back(records.at(i));
        }
    }

    std::cout << "Found " << multipleChildCount << " nodes with multiple children" << std::endl;
    std::cout << "Found " << noChildrenCount << " nodes with no children" << std::endl;
    std::cout << "Found " << singleChildCount << " nodes with exactly one child" << std::endl;

}

void buildSize8Chains(std::vector<DataRecord> const & records, std::vector<std::vector<size_t> > & chains)
{
    chains.clear();
    size_t longestChain = 0;
    size_t longestChainIndex = 0;
    /* With our 538 'good' nodes attempt to build chains of them */
    for (size_t initialLink = 0; initialLink < records.size(); initialLink++)
    {
        std::vector<size_t> chain;
        chain.push_back(initialLink);
        size_t previousLink = initialLink;
        while (true)
        {
            bool foundChild = false;
            for (size_t possibleNextLink = 0; possibleNextLink < records.size(); possibleNextLink++)
            {
                if (records.at(previousLink).mutatedSummary_ == records.at(possibleNextLink).originalSummary_)
                {
                    /* Make sure we're not circling ourselves... */
                    bool isCircle = false;
                    for (std::vector<size_t>::const_iterator it = chain.begin(); it != chain.end(); ++it)
                    {
                        if (*it == possibleNextLink)
                        {
                            isCircle = true;
                        }
                    }

                    if ( false == isCircle)
                    {
                        foundChild = true;
                        chain.push_back(possibleNextLink);
                        previousLink = possibleNextLink;
                    }
                    break;
                }
            }
            if (foundChild == false)
            {
                /* End of a chain... */
                break;
            }
        }
        if (chain.size() > longestChain)
        {
            longestChain = chain.size();
            longestChainIndex = chain.at(0);
        }
        if (chain.size() == 8)
        {
            chains.push_back(chain);
        }

    }
    std::cout << "Generated " << chains.size() << " size-8 chains." << std::endl;
    std::cout << "Longest Chain is " << longestChain << " links." << std::endl;
}

void convertTextToRecords(CSVOutput_t const & csvResults, std::vector<DataRecord> & rawRecords)
{
    rawRecords.clear();
    size_t totalProcessedRecords;
    size_t validRecords = 0;
    size_t discardedRecords_WrongFieldCount = 0;
    size_t discardedRecords_InvalidOriginalNodeSymbol = 0;
    size_t discardedRecords_InvalidMutatedNodeSymbol = 0;
    for (CSVOutput_t::const_iterator it =csvResults.begin(); it != csvResults.end(); ++it)
    {
        totalProcessedRecords++;
        /* First line is timestamp, ignore for now... */
        if (it->size() != EXPECTED_FIELD_COUNT)
        {
            discardedRecords_WrongFieldCount++;
            continue;
        }
        DataRecord newRecord;
        /* Field #0 is the time stamp" */
        newRecord.username_ = it->at(1);
        /* Attempt to process the original node symbols */
        bool hasBadOriginalSymbol = false;
        for (size_t i = 2; i < 7; i++)
        {
            if ("Square" == it->at(i))
            {
                newRecord.originalNode_[i - 2] = SYMBOL::SQUARE;
            }
            else if ("Circle" == it->at(i))
            {
                newRecord.originalNode_[i - 2] = SYMBOL::CIRCLE;
            }
            else if ("Triangle" == it->at(i))
            {
                newRecord.originalNode_[i - 2] = SYMBOL::TRIANGLE;
            }
            else if ("Diamond" == it->at(i))
            {
                newRecord.originalNode_[i - 2] = SYMBOL::DIAMOND;
            }
            else
            {
                hasBadOriginalSymbol = true;
                break;
            }
        }
        if (true == hasBadOriginalSymbol)
        {
            discardedRecords_InvalidOriginalNodeSymbol++;
            continue;
        }
        /* Get symbol summary string */
        std::string upperCaseOriginalSummary = it->at(7);
        std::transform(upperCaseOriginalSummary.begin(), upperCaseOriginalSummary.end(),upperCaseOriginalSummary.begin(), ::toupper);
        newRecord.originalSummary_ = upperCaseOriginalSummary;

        bool hasBadMutatedSymbol = false;
        for (size_t i = 8; i < 13; i++)
        {
            if ("Square" == it->at(i))
            {
                newRecord.mutatedNode_[i - 8] = SYMBOL::SQUARE;
            }
            else if ("Circle" == it->at(i))
            {
                newRecord.mutatedNode_[i - 8] = SYMBOL::CIRCLE;
            }
            else if ("Triangle" == it->at(i))
            {
                newRecord.mutatedNode_[i - 8] = SYMBOL::TRIANGLE;
            }
            else if ("Diamond" == it->at(i))
            {
                newRecord.mutatedNode_[i - 8] = SYMBOL::DIAMOND;
            }
            else
            {
                hasBadMutatedSymbol = true;
                break;
            }
        }

        if (true == hasBadMutatedSymbol)
        {
            discardedRecords_InvalidMutatedNodeSymbol++;
            continue;
        }

        std::string upperCaseMutatedSummary = it->at(13);
        std::transform(upperCaseMutatedSummary.begin(), upperCaseMutatedSummary.end(),upperCaseMutatedSummary.begin(), ::toupper);
        newRecord.mutatedSummary_ = upperCaseMutatedSummary;

        newRecord.processingKey_ = it->at(14);
        newRecord.iv_ = it->at(15);
        newRecord.encryptedBytes_ = it->at(16);
        validRecords++;
        rawRecords.push_back(newRecord);
    } /* End of iterating over symbols */

    std::cout << "Received " << totalProcessedRecords << " total records" << std::endl;
    std::cout << "Discarded " << discardedRecords_WrongFieldCount << " records due to wrong field count" << std::endl;
    std::cout << "Discarded " << discardedRecords_InvalidOriginalNodeSymbol << " records due to invalid original node symbols" << std::endl;
    std::cout << "Discarded " << discardedRecords_InvalidMutatedNodeSymbol << " records due to invalid mutated node symbols" << std::endl;
    std::cout << "Processed " << validRecords << " valid records" << std::endl;
}



void sanitizeRecords(std::vector<DataRecord> const & rawRecords, std::vector<DataRecord> & sanitizedRecords)
{
    sanitizedRecords.clear();
    for (std::vector<DataRecord>::const_iterator it = rawRecords.begin(); it != rawRecords.end(); ++it)
    {
        if (it->username_.length() < 1)
        {
            continue;
        }
        /* Check original symbol list */
        std::stringstream ssExpectedOriginalSummary;
        for (size_t i = 0; i < 5; i++)
        {
            switch(it->originalNode_[i])
            {
                default: break;
                case SYMBOL::CIRCLE: ssExpectedOriginalSummary << "C"; break;
                case SYMBOL::SQUARE: ssExpectedOriginalSummary << "S"; break;
                case SYMBOL::TRIANGLE: ssExpectedOriginalSummary << "T"; break;
                case SYMBOL::DIAMOND: ssExpectedOriginalSummary << "D"; break;
            };
        }
        std::string const expectedOriginalSummary = ssExpectedOriginalSummary.str();
        std::string sanitizedOriginalSummary = it->originalSummary_;
        std::transform(sanitizedOriginalSummary.begin(), sanitizedOriginalSummary.end(),sanitizedOriginalSummary.begin(), ::toupper);
        if (expectedOriginalSummary != sanitizedOriginalSummary)
        {
            continue;
        }

        /* Check mutated symbol list */
        std::stringstream ssExpectedMutatedSummary;
        for (size_t i = 0; i < 5; i++)
        {
            switch(it->mutatedNode_[i])
            {
                default: break;
                case SYMBOL::CIRCLE: ssExpectedMutatedSummary << "C"; break;
                case SYMBOL::SQUARE: ssExpectedMutatedSummary << "S"; break;
                case SYMBOL::TRIANGLE: ssExpectedMutatedSummary << "T"; break;
                case SYMBOL::DIAMOND: ssExpectedMutatedSummary << "D"; break;
            };
        }
        std::string const expectedMutatedSummary = ssExpectedMutatedSummary.str();
        std::string sanitizedMutatedSummary = it->mutatedSummary_;
        std::transform(sanitizedMutatedSummary.begin(), sanitizedMutatedSummary.end(),sanitizedMutatedSummary.begin(), ::toupper);
        if (expectedMutatedSummary != sanitizedMutatedSummary)
        {
            continue;
        }

        /* Key portion should ALL be 8 bytes */
        if (it->processingKey_.length() != 8)
        {
            continue;
        }
        /* Initial vectors should all be 24 bytes long */
        if (it->iv_.length() != 24)
        {
            continue;
        }
        if (it->encryptedBytes_.size() < 128)
        {
            continue;
        }
        sanitizedRecords.push_back(*it);
    }
}
