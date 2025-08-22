#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "fenwick_tree.hpp"

/**
 * @brief Represents a candidate in the election
 */
struct Candidate {
    std::string name;
    std::string party;
    std::string id;
    
    Candidate(const std::string& n, const std::string& p, const std::string& i)
        : name(n), party(p), id(i) {}
};

/**
 * @brief Represents a district in the election
 */
struct District {
    std::string name;
    std::string id;
    size_t candidateCount;
    
    District(const std::string& n, const std::string& i, size_t cc)
        : name(n), id(i), candidateCount(cc) {}
};

/**
 * @brief Represents a vote update event
 */
struct VoteUpdate {
    std::string districtId;
    std::string candidateId;
    int64_t voteCount;
    std::string precinctId;
    std::string timestamp;
    
    VoteUpdate(const std::string& d, const std::string& c, int64_t v, 
               const std::string& p, const std::string& t)
        : districtId(d), candidateId(c), voteCount(v), precinctId(p), timestamp(t) {}
};

/**
 * @brief Manages vote counting operations using Fenwick Trees
 * 
 * This class provides the core functionality for:
 * - Adding/updating votes for candidates in districts
 * - Querying vote totals at various granularity levels
 * - Managing candidates and districts
 * - Real-time vote aggregation
 */
class VoteManager {
private:
    // District ID -> Fenwick Tree mapping
    // Each Fenwick Tree handles votes for all candidates in that district
    std::unordered_map<std::string, std::unique_ptr<FenwickTree>> districtTrees;
    
    // Candidate ID -> index mapping within each district
    std::unordered_map<std::string, std::unordered_map<std::string, size_t>> candidateIndices;
    
    // District and candidate information
    std::vector<District> districts;
    std::vector<Candidate> candidates;
    
    // Vote history for audit purposes
    std::vector<VoteUpdate> voteHistory;

public:
    /**
     * @brief Add a new district to the system
     * @param district The district to add
     */
    void addDistrict(const District& district);
    
    /**
     * @brief Add a new candidate to the system
     * @param candidate The candidate to add
     */
    void addCandidate(const Candidate& candidate);
    
    /**
     * @brief Assign a candidate to a district
     * @param districtId The district ID
     * @param candidateId The candidate ID
     */
    void assignCandidateToDistrict(const std::string& districtId, const std::string& candidateId);
    
    /**
     * @brief Add votes for a candidate in a district
     * @param districtId The district ID
     * @param candidateId The candidate ID
     * @param voteCount The number of votes to add
     * @param precinctId The precinct ID (for tracking)
     * @param timestamp The timestamp of the update
     */
    void addVotes(const std::string& districtId, const std::string& candidateId, 
                  int64_t voteCount, const std::string& precinctId, const std::string& timestamp);
    
    /**
     * @brief Get total votes for a candidate in a district
     * @param districtId The district ID
     * @param candidateId The candidate ID
     * @return Total votes for the candidate in the district
     */
    int64_t getCandidateVotes(const std::string& districtId, const std::string& candidateId) const;
    
    /**
     * @brief Get total votes for a candidate across all districts
     * @param candidateId The candidate ID
     * @return Total votes for the candidate across all districts
     */
    int64_t getCandidateTotalVotes(const std::string& candidateId) const;
    
    /**
     * @brief Get total votes in a district
     * @param districtId The district ID
     * @return Total votes in the district
     */
    int64_t getDistrictTotalVotes(const std::string& districtId) const;
    
    /**
     * @brief Get the leading candidate in a district
     * @param districtId The district ID
     * @return The candidate ID with the most votes, or empty string if no votes
     */
    std::string getDistrictLeader(const std::string& districtId) const;
    
    /**
     * @brief Get the overall election leader
     * @return The candidate ID with the most total votes, or empty string if no votes
     */
    std::string getOverallLeader() const;
    
    /**
     * @brief Get vote history for audit purposes
     * @return Vector of vote updates
     */
    const std::vector<VoteUpdate>& getVoteHistory() const { return voteHistory; }
    
    /**
     * @brief Get all districts
     * @return Vector of districts
     */
    const std::vector<District>& getDistricts() const { return districts; }
    
    /**
     * @brief Get all candidates
     * @return Vector of candidates
     */
    const std::vector<Candidate>& getCandidates() const { return candidates; }
    
    /**
     * @brief Reset all vote counts to zero
     */
    void resetVotes();
    
    /**
     * @brief Get detailed results for all districts
     * @return Formatted string with election results
     */
    std::string getDetailedResults() const;
};
