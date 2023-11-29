#ifndef IMPEDANCEREADER_H
#define IMPEDANCEREADER_H

#include <vector>
#include <deque>
#include "systemstate.h"
#include "rhsaccess.h"

using namespace std;

struct ComplexPolar {
    double magnitude;
    double phase;
};

class ImpedanceReader:public QObject
{
    Q_OBJECT
public:
    ImpedanceReader(QObject *parent = nullptr);

    void measureImpedances();

    void runDemoImpedanceMeasurement();

    RHSAccess rhsra;
};

#endif // IMPEDANCEREADER_H
