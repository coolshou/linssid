/*
 * File:   mainForm.h
 * Author: warren
 *
 * Created on October 25, 2012, 11:43 AM
 */

#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include <iostream>
#include <fstream>
#include <QEvent>
#include <QString>
#include <QFont>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_draw.h>
#include "ui_MainForm.h"
#include "prefsDialog.h"
#include "Custom.h"
#include "DataStruct.h"
#include "DataLogger.h"
#include "PrefsHandler.h"
#include "VendorDb.h"

class Getter; // forward declare

class MainForm : public QMainWindow {
    Q_OBJECT
public:

    MainForm();
    virtual ~MainForm();
    //    void run();
    void init();
    void getUserID();
    void addInterfaces();
    void setInterface(int);
    int getNapTime();
    std::string getCurrentInterface();
    static const QEvent::Type DATA_READY_EVENT;
    class DataReadyEvent;
    int getReadyBlockNo();
    void postDataReadyEvent(const int);
    void drawTable();
    void setVisibleCols();
    void fillTable();
    class Chan24ScaleDraw;
    class Chan5ScaleDraw;
    void initColtoAction();
    void initPlotGrids();
    void initStatusBar();
    void drawChan24Plot();
    void drawChan5Plot();
    void drawTimePlot();
    void fillPlots();
    void fillStatus();
    void initNewCell(std::string, int);
    void extractData(std::string, int &, int &);
    void resolveMesh(int);

    static Getter* pGetter; // a pointer to the instance of the Getter that calls this MainForm
    static QThread* pGetterThread; // a pointer to the getter's thread
    static CellData::Vector cellDataRay;
    static int maxTableIndex;
    static long runStartTime;
    static long blockSampleTime;
    static long now;
    static int logDataState;
    static bool firstScan;
    static QFont tblFnt;
    static QString fntSizes[];
    static int numFntSizes;
    static QAction* colToQAction[MAX_TABLE_COLS];
    static int columnWidth[MAX_TABLE_COLS];
    std::unique_ptr<QwtPlotGrid> chan24Grid;
    std::unique_ptr<QwtPlotGrid> chan5Grid;
    std::unique_ptr<QwtPlotGrid> timeGrid;
    std::unique_ptr<prefsDialog> prefsDlg;

public slots:
    void doRun();
    void doPlotAll();
    void doPlotNone();
    void doTableChanged(int,int);
    void reDrawTable();
    void showAboutBox();
    void showPrefsDlg();
    void columnWidthSave(int, int, int);
    void updatePlotPrefs(QString, int, int, bool, bool);
    void logPrefChanged(int);

protected:
    Ui::mainForm mainFormWidget;
    void customEvent(QEvent*); // This overrides QObject::customEvent()
    void closeEvent(QCloseEvent*); // Overides built-in closeEvent()
    void handleDataReadyEvent(const DataReadyEvent*);

private:
    void savePrefs();
    void loadPrefs();
    void applyPlotPrefs(int fntSize, int plotMin, int plotMax, bool showGrid);

private:
    std::unique_ptr<DataLogger> dataLogger;
    std::unique_ptr<VendorDb> vendorDb;
    std::unique_ptr<PrefsHandler> prefsHandler;
    std::unique_ptr<QLabel> statusCounts;
    Stats stats;

    bool plotShowLabel = true;
};

#endif	/* _MAINFORM_H */
