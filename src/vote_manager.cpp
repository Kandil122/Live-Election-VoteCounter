#include "vote_manager.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
using namespace std;

void VoteManager::addDistrict(const District& district) {
    districts.push_back(district);
    
    // Create a Fenwick Tree for this district with capacity for all candidates
    districtTrees[district.id] = std::make_unique<FenwickTree>(district.candidateCount);
    
    // Initialize candidate indices for this district
    candidateIndices[district.id] = std::unordered_map<std::string, size_t>();
}

void VoteManager::addCandidate(const Candidate& candidate) {
    candidates.push_back(candidate);
}

void VoteManager::assignCandidateToDistrict(const std::string& districtId, const std::string& candidateId) {
    auto districtIt = std::find_if(districts.begin(), districts.end(),
        [&districtId](const District& d) { return d.id == districtId; });
    
    if (districtIt == districts.end()) {
        throw std::runtime_error("District not found: " + districtId);
    }
    
    auto candidateIt = std::find_if(candidates.begin(), candidates.end(),
        [&candidateId](const Candidate& c) { return c.id == candidateId; });
    
    if (candidateIt == candidates.end()) {
        throw std::runtime_error("Candidate not found: " + candidateId);
    }
    
    // Assign the next available index in this district
    size_t nextIndex = candidateIndices[districtId].size() + 1;
    candidateIndices[districtId][candidateId] = nextIndex;
}

void VoteManager::addVotes(const std::string& districtId, const std::string& candidateId, 
                           int64_t voteCount, const std::string& precinctId, const std::string& timestamp) {
    // Validate district exists
    auto districtIt = districtTrees.find(districtId);
    if (districtIt == districtTrees.end()) {
        throw std::runtime_error("District not found: " + districtId);
    }
    
    // Validate candidate exists in this district
    auto candidateIndexIt = candidateIndices.find(districtId);
    if (candidateIndexIt == candidateIndices.end()) {
        throw std::runtime_error("No candidates assigned to district: " + districtId);
    }
    
    auto indexIt = candidateIndexIt->second.find(candidateId);
    if (indexIt == candidateIndexIt->second.end()) {
        throw std::runtime_error("Candidate not found in district: " + candidateId + " in " + districtId);
    }
    
    // Update the Fenwick Tree (1-based indexing)
    size_t candidateIndex = indexIt->second;
    districtIt->second->update(candidateIndex, voteCount);
    
    // Record the vote update for audit
    voteHistory.emplace_back(districtId, candidateId, voteCount, precinctId, timestamp);
}

int64_t VoteManager::getCandidateVotes(const std::string& districtId, const std::string& candidateId) const {
    auto districtIt = districtTrees.find(districtId);
    if (districtIt == districtTrees.end()) {
        return 0;
    }
    
    auto candidateIndexIt = candidateIndices.find(districtId);
    if (candidateIndexIt == candidateIndices.end()) {
        return 0;
    }
    
    auto indexIt = candidateIndexIt->second.find(candidateId);
    if (indexIt == candidateIndexIt->second.end()) {
        return 0;
    }
    
    // Get the value at the candidate's index (1-based)
    return districtIt->second->getValue(indexIt->second);
}

int64_t VoteManager::getCandidateTotalVotes(const std::string& candidateId) const {
    int64_t total = 0;
    
    for (const auto& district : districts) {
        total += getCandidateVotes(district.id, candidateId);
    }
    
    return total;
}

int64_t VoteManager::getDistrictTotalVotes(const std::string& districtId) const {
    auto districtIt = districtTrees.find(districtId);
    if (districtIt == districtTrees.end()) {
        return 0;
    }
    
    // Get the sum of all candidates in this district
    return districtIt->second->query(districtIt->second->getSize());
}

    string VoteManager::getDistrictLeader(const std::string& districtId) const {
    auto districtIt = districtTrees.find(districtId);
    if (districtIt == districtTrees.end()) {
        return "";
    }
    
    auto candidateIndexIt = candidateIndices.find(districtId);
    if (candidateIndexIt == candidateIndices.end()) {
        return "";
    }
    
        string leaderId = "";
    int64_t maxVotes = -1;
    
    // Find the candidate with the most votes in this district
    for (const auto& candidate : candidates) {
        int64_t votes = getCandidateVotes(districtId, candidate.id);
        if (votes > maxVotes) {
            maxVotes = votes;
            leaderId = candidate.id;
        }
    }
    
    return leaderId;
}

    string VoteManager::getOverallLeader() const {
        string leaderId = "";
    int64_t maxVotes = -1;
    
    // Find the candidate with the most total votes across all districts
    for (const auto& candidate : candidates) {
        int64_t totalVotes = getCandidateTotalVotes(candidate.id);
        if (totalVotes > maxVotes) {
            maxVotes = totalVotes;
            leaderId = candidate.id;
        }
    }
    
    return leaderId;
}

void VoteManager::resetVotes() {
    for (auto& districtTree : districtTrees) {
        districtTree.second->reset();
    }
    voteHistory.clear();
}

    string VoteManager::getDetailedResults() const {
    std::ostringstream oss;
    oss << "=== ELECTION RESULTS ===\n\n";
    
    // Overall results
    std::string overallLeader = getOverallLeader();
    if (!overallLeader.empty()) {
        auto leaderIt = std::find_if(candidates.begin(), candidates.end(),
            [&overallLeader](const Candidate& c) { return c.id == overallLeader; });
        if (leaderIt != candidates.end()) {
            int64_t totalVotes = getCandidateTotalVotes(overallLeader);
            oss << "OVERALL LEADER: " << leaderIt->name << " (" << leaderIt->party << ") - " 
                << totalVotes << " votes\n\n";
        }
    }
    
    // Results by district
    for (const auto& district : districts) {
        oss << "DISTRICT: " << district.name << " (" << district.id << ")\n";
        oss << std::string(40, '-') << "\n";
        
        // Get all candidates in this district with their vote counts
        std::vector<std::pair<std::string, int64_t>> districtResults;
        for (const auto& candidate : candidates) {
            int64_t votes = getCandidateVotes(district.id, candidate.id);
            if (votes > 0) {
                districtResults.emplace_back(candidate.id, votes);
            }
        }
        
        // Sort by vote count (descending)
        std::sort(districtResults.begin(), districtResults.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
        
        for (const auto& result : districtResults) {
            auto candidateIt = std::find_if(candidates.begin(), candidates.end(),
                [&result](const Candidate& c) { return c.id == result.first; });
            if (candidateIt != candidates.end()) {
                oss << std::setw(20) << std::left << candidateIt->name
                    << " (" << candidateIt->party << "): " << result.second << " votes\n";
            }
        }
        
        int64_t districtTotal = getDistrictTotalVotes(district.id);
        oss << std::string(40, '-') << "\n";
        oss << "TOTAL DISTRICT VOTES: " << districtTotal << "\n\n";
    }
    
    return oss.str();
}
