#pragma once
#include <string>
#include <vector>
#include <memory>
#include "vote_manager.hpp"

/**
 * @brief High-level election management system
 * 
 * This class provides a user-friendly interface for:
 * - Setting up elections with districts and candidates
 * - Processing vote updates in real-time
 * - Generating reports and analytics
 * - Managing the overall election workflow
 */
class ElectionSystem {
private:
    std::unique_ptr<VoteManager> voteManager;
    std::string electionName;
    std::string electionDate;
    bool isActive;

public:
    /**
     * @brief Construct the election system
     * @param name The name of the election
     * @param date The date of the election
     */
    ElectionSystem(const std::string& name, const std::string& date);
    
    /**
     * @brief Set up the election structure
     * @param districtNames Vector of district names
     * @param candidateNames Vector of candidate names
     * @param partyNames Vector of party names (corresponding to candidates)
     */
    void setupElection(const std::vector<std::string>& districtNames,
                       const std::vector<std::string>& candidateNames,
                       const std::vector<std::string>& partyNames);
    
    /**
     * @brief Process a vote update from a precinct
     * @param districtName The district name
     * @param candidateName The candidate name
     * @param voteCount The number of votes
     * @param precinctId The precinct identifier
     * @return True if the update was successful
     */
    bool processVoteUpdate(const std::string& districtName,
                          const std::string& candidateName,
                          int64_t voteCount,
                          const std::string& precinctId);
    
    /**
     * @brief Get current election results
     * @return Formatted string with current results
     */
    std::string getCurrentResults() const;
    
    /**
     * @brief Get results for a specific district
     * @param districtName The district name
     * @return Formatted string with district results
     */
    std::string getDistrictResults(const std::string& districtName) const;
    
    /**
     * @brief Get results for a specific candidate
     * @param candidateName The candidate name
     * @return Formatted string with candidate results
     */
    std::string getCandidateResults(const std::string& candidateName) const;
    
    /**
     * @brief Get the current election leader
     * @return The name of the leading candidate
     */
    std::string getCurrentLeader() const;
    
    /**
     * @brief Get vote history for audit
     * @return Vector of vote updates
     */
    std::vector<VoteUpdate> getVoteHistory() const;
    
    /**
     * @brief Reset the election (clear all votes)
     */
    void resetElection();
    
    /**
     * @brief Check if the election is active
     * @return True if the election is active
     */
    bool isElectionActive() const { return isActive; }
    
    /**
     * @brief Set election status
     * @param active Whether the election should be active
     */
    void setElectionStatus(bool active) { isActive = active; }
    
    /**
     * @brief Get election information
     * @return Formatted string with election details
     */
    std::string getElectionInfo() const;
    
    /**
     * @brief Simulate random vote updates for testing
     * @param numUpdates Number of updates to simulate
     */
    void simulateRandomUpdates(int numUpdates);
    
    /**
     * @brief Get access to the VoteManager for detailed operations
     * @return Pointer to the VoteManager
     */
    const VoteManager* getVoteManager() const { return voteManager.get(); }
};
