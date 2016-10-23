#pragma once

#include <string>


enum class SYMBOL : uint8_t
{
    CIRCLE = 1,
    SQUARE = 2,
    TRIANGLE = 3,
    DIAMOND = 4,
};

struct DataRecord
{
    std::string username_;
    SYMBOL originalNode_[5];
    std::string originalSummary_;
    SYMBOL mutatedNode_[5];
    std::string mutatedSummary_;
    std::string processingKey_;
    std::string iv_;
    std::string encryptedBytes_;
};

inline bool operator==(const DataRecord& lhs, const DataRecord& rhs)
{
    if (lhs.originalSummary_ != rhs.originalSummary_)
    {
        return false;
    }
    if (lhs.mutatedSummary_ != rhs.mutatedSummary_)
    {
        return false;
    }
    if (lhs.processingKey_ != rhs.processingKey_)
    {
        return false;
    }
    if (lhs.iv_ != rhs.iv_)
    {
        return false;
    }
    if (lhs.encryptedBytes_ != rhs.encryptedBytes_)
    {
        return false;
    }

    return true;
}

struct ChainNode
{
    size_t index_;
    std::vector<size_t> children_;
};
