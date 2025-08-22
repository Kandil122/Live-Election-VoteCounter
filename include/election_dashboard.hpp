#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QTableWidget>
#include <QCheckBox>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QGroupBox>
#include <QProgressBar>
#include <QTimer>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QComboBox>
#include <QMessageBox>
#include <QStatusBar>
#include <QMenuBar>
#include <QInputDialog>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QApplication>
#include <QStyle>
#include <QSplitter>
#include <QScrollArea>
#include <QFrame>
#include <QHeaderView>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

#include "election_system.hpp"

QT_CHARTS_USE_NAMESPACE

/**
 * @brief Main GUI Dashboard for the Live Election Vote Counter
 * 
 * Provides a real-time interface with:
 * - Live vote updates
 * - Real-time charts and graphs
 * - District and candidate results
 * - Vote history tracking
 * - Interactive controls
 */
class ElectionDashboard : public QMainWindow {
    Q_OBJECT

public:
    explicit ElectionDashboard(QWidget *parent = nullptr);
    ~ElectionDashboard();

private slots:
    // Setup and control
    void setupElection();
    void startElection();
    void stopElection();
    void resetElection();
    
    // Vote management
    void addVoteUpdate();
    void simulateRandomUpdates();
    
    // View updates
    void refreshResults();
    void exportResults();
    void showAbout();
    
    // Real-time updates
    void updateDashboard();
    void updateCharts();
    void updateTables();
    
    // Auto-refresh
    void toggleAutoRefresh();
    void setRefreshInterval(int seconds);

private:
    // Core system
    std::unique_ptr<ElectionSystem> electionSystem;
    
    // UI Components
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;
    
    // Control Panel
    QGroupBox *controlGroup;
    QPushButton *setupButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *resetButton;
    QLabel *statusLabel;
    QLabel *electionInfoLabel;
    
    // Vote Input Panel
    QGroupBox *voteInputGroup;
    QComboBox *districtCombo;
    QComboBox *candidateCombo;
    QSpinBox *voteCountSpin;
    QLineEdit *precinctEdit;
    QPushButton *addVoteButton;
    QPushButton *simulateButton;
    QSpinBox *simulateCountSpin;
    
    // Results Display
    QGroupBox *resultsGroup;
    QTextEdit *resultsText;
    QPushButton *refreshButton;
    QPushButton *exportButton;
    
    // Charts
    QChartView *overallChartView;
    QChartView *districtChartView;
    QChart *overallChart;
    QChart *districtChart;
    QBarSeries *overallBarSeries;
    QBarSeries *districtBarSeries;
    
    // Tables
    QTableWidget *districtTable;
    QTableWidget *candidateTable;
    QTableWidget *historyTable;
    
    // Real-time features
    QTimer *updateTimer;
    QTimer *autoRefreshTimer;
    QCheckBox *autoRefreshCheck;
    QSpinBox *refreshIntervalSpin;
    QProgressBar *updateProgressBar;
    
    // Menu and status
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QStatusBar *statusBar;
    
    // Methods
    void setupUI();
    void setupCharts();
    void setupTables();
    void setupMenus();
    void setupConnections();
    void updateElectionInfo();
    void populateComboBoxes();
    void createCharts();
    void updateOverallChart();
    void updateDistrictChart();
    void updateDistrictTable();
    void updateCandidateTable();
    void updateHistoryTable();
    void showStatusMessage(const QString &message, int timeout = 3000);
    void logActivity(const QString &activity);
    
    // Constants
    static const int DEFAULT_REFRESH_INTERVAL = 5; // seconds
    static const int MAX_HISTORY_ROWS = 1000;
};
