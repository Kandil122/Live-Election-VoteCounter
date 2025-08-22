#include "election_system.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <ctime>
using namespace std;

// constructor , b intializie el values el 3ndi
ElectionSystem::ElectionSystem(const std::string& name, const std::string& date)
    : voteManager(std::make_unique<VoteManager>()), electionName(name), electionDate(date), isActive(false) {
}

// function b setupElection
void ElectionSystem::setupElection(const std::vector<std::string>& districtNames,
                                   const std::vector<std::string>& candidateNames,
                                   const std::vector<std::string>& partyNames) {
    if (candidateNames.size() != partyNames.size()) {
        throw std::invalid_argument("Number of candidates must match number of parties");
    }
    
    // Add districts
    for (size_t i = 0; i < districtNames.size(); ++i) {
        std::string districtId = "D" + std::to_string(i + 1);
        District district(districtNames[i], districtId, candidateNames.size());
        voteManager->addDistrict(district);
    }
    
    // Add candidates
    for (size_t i = 0; i < candidateNames.size(); ++i) {
        std::string candidateId = "C" + std::to_string(i + 1);
        Candidate candidate(candidateNames[i], partyNames[i], candidateId);
        voteManager->addCandidate(candidate);
    }
    
    // Assign all candidates to all districts
    for (const auto& district : voteManager->getDistricts()) {
        for (const auto& candidate : voteManager->getCandidates()) {
            voteManager->assignCandidateToDistrict(district.id, candidate.id);
        }
    }
}

bool ElectionSystem::processVoteUpdate(const std::string& districtName,
                                       const std::string& candidateName,
                                       int64_t voteCount,
                                       const std::string& precinctId) {
    if (!isActive) {
        return false;
    }
    
    try {
        // Find district by name
        auto districts = voteManager->getDistricts();
        auto districtIt = std::find_if(districts.begin(), districts.end(),
            [&districtName](const District& d) { return d.name == districtName; });
        
        if (districtIt == districts.end()) {
            return false;
        }
        
        // Find candidate by name
        auto candidates = voteManager->getCandidates();
        auto candidateIt = std::find_if(candidates.begin(), candidates.end(),
            [&candidateName](const Candidate& c) { return c.name == candidateName; });
        
        if (candidateIt == candidates.end()) {
            return false;
        }
        
        // Generate timestamp
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::string timestamp = std::ctime(&time_t);
        timestamp.pop_back(); // Remove newline
        
        // Process the vote update
        voteManager->addVotes(districtIt->id, candidateIt->id, voteCount, precinctId, timestamp);
        return true;
        
    } catch (const std::exception& e) {
        return false;
    }
}

    string ElectionSystem::getCurrentResults() const {
    return voteManager->getDetailedResults();
}

    string ElectionSystem::getDistrictResults(const std::string& districtName) const {
    auto districts = voteManager->getDistricts();
    auto districtIt = std::find_if(districts.begin(), districts.end(),
        [&districtName](const District& d) { return d.name == districtName; });
    
    if (districtIt == districts.end()) {
        return "District not found: " + districtName;
    }
    
    std::ostringstream oss;
    oss << "=== DISTRICT RESULTS: " << districtName << " ===\n\n";
    
    auto candidates = voteManager->getCandidates();
    std::vector<std::pair<std::string, int64_t>> districtResults;
    
    for (const auto& candidate : candidates) {
        int64_t votes = voteManager->getCandidateVotes(districtIt->id, candidate.id);
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
    
    int64_t districtTotal = voteManager->getDistrictTotalVotes(districtIt->id);
    oss << "\nTOTAL DISTRICT VOTES: " << districtTotal << "\n";
    
    return oss.str();
}

    string ElectionSystem::getCandidateResults(const std::string& candidateName) const {
    auto candidates = voteManager->getCandidates();
    auto candidateIt = std::find_if(candidates.begin(), candidates.end(),
        [&candidateName](const Candidate& c) { return c.name == candidateName; });
    
    if (candidateIt == candidates.end()) {
        return "Candidate not found: " + candidateName;
    }
    
    std::ostringstream oss;
    oss << "=== CANDIDATE RESULTS: " << candidateName << " (" << candidateIt->party << ") ===\n\n";
    
    auto districts = voteManager->getDistricts();
    int64_t totalVotes = 0;
    
    for (const auto& district : districts) {
        int64_t votes = voteManager->getCandidateVotes(district.id, candidateIt->id);
        if (votes > 0) {
            oss << std::setw(20) << std::left << district.name << ": " << votes << " votes\n";
            totalVotes += votes;
        }
    }
    
    oss << "\nTOTAL VOTES: " << totalVotes << "\n";
    
    return oss.str();
}

    string ElectionSystem::getCurrentLeader() const {
        string leaderId = voteManager->getOverallLeader();
    if (leaderId.empty()) {
        return "No votes cast yet";
    }
    
    auto candidates = voteManager->getCandidates();
    auto leaderIt = std::find_if(candidates.begin(), candidates.end(),
        [&leaderId](const Candidate& c) { return c.id == leaderId; });
    
    if (leaderIt != candidates.end()) {
        int64_t totalVotes = voteManager->getCandidateTotalVotes(leaderId);
        return leaderIt->name + " (" + leaderIt->party + ") - " + std::to_string(totalVotes) + " votes";
    }
    
    return "Unknown leader";
}

    vector<VoteUpdate> ElectionSystem::getVoteHistory() const {
    return voteManager->getVoteHistory();
}

void ElectionSystem::resetElection() {
    voteManager->resetVotes();
}

    string ElectionSystem::getElectionInfo() const {
        ostringstream oss;
    oss << "=== ELECTION INFORMATION ===\n";
    oss << "Name: " << electionName << "\n";
    oss << "Date: " << electionDate << "\n";
    oss << "Status: " << (isActive ? "ACTIVE" : "INACTIVE") << "\n";
    oss << "Districts: " << voteManager->getDistricts().size() << "\n";
    oss << "Candidates: " << voteManager->getCandidates().size() << "\n";
    oss << "Total Votes Cast: " << voteManager->getVoteHistory().size() << " updates\n";
    
    return oss.str();
}

void ElectionSystem::simulateRandomUpdates(int numUpdates) {
    if (!isActive) {
        return;
    }
    
    auto districts = voteManager->getDistricts();
    auto candidates = voteManager->getCandidates();
    
    if (districts.empty() || candidates.empty()) {
        return;
    }
    
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> districtDist(0, districts.size() - 1);
        uniform_int_distribution<> candidateDist(0, candidates.size() - 1);
        uniform_int_distribution<> voteDist(1, 100);
        uniform_int_distribution<> precinctDist(1, 999);
    
    for (int i = 0; i < numUpdates; ++i) {
        const auto& district = districts[districtDist(gen)];
        const auto& candidate = candidates[candidateDist(gen)];
        int64_t voteCount = voteDist(gen);
            string precinctId = "P" + std::to_string(precinctDist(gen));
        
        processVoteUpdate(district.name, candidate.name, voteCount, precinctId);
    }
}
