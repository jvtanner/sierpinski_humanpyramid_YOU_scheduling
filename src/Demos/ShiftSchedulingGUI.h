#ifndef ShiftSchedulingGUI_Included
#define ShiftSchedulingGUI_Included

#include "ProblemHandler.h"
#include "ShiftScheduling.h"
#include "TemporaryComponent.h"
#include "ginteractors.h"
#include <fstream>

/* Problem handler to visualize the sorts of shifts that would be generated by
 * an optimal scheduler.
*/
class ShiftSchedulingGUI: public ProblemHandler {
public:
    ShiftSchedulingGUI(GWindow& window);
    static std::string name();

    void actionPerformed(GObservable* source) override;

protected:
    void repaint(GWindow& window) override;

private:
    struct Impl;
    std::shared_ptr<Impl> mImpl;
};

#endif
