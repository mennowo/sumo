/***************************************************************************
                          MSLogicJunction.cpp  -  Base class for junctions
                          with one ore more logics.
                             -------------------
    begin                : Wed, 12 Dez 2001
    copyright            : (C) 2001 by Christian Roessel
    email                : roessel@zpr.uni-koeln.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
namespace
{
    const char rcsid[] =
    "$Id$";
}
// $Log$
// Revision 1.14  2006/11/16 12:30:54  dkrajzew
// warnings removed
//
// Revision 1.13  2006/10/06 07:13:40  dkrajzew
// debugging internal lanes
//
// Revision 1.12  2006/02/23 11:27:56  dkrajzew
// tls may have now several programs
//
// Revision 1.11  2005/10/07 11:37:45  dkrajzew
// THIRD LARGE CODE RECHECK: patched problems on Linux/Windows configs
//
// Revision 1.10  2005/09/22 13:45:51  dkrajzew
// SECOND LARGE CODE RECHECK: converted doubles and floats to SUMOReal
//
// Revision 1.9  2005/09/15 11:10:46  dkrajzew
// LARGE CODE RECHECK
//
// Revision 1.8  2004/08/02 12:09:39  dkrajzew
// using Position2D instead of two SUMOReals
//
// Revision 1.7  2003/12/04 13:30:41  dkrajzew
// work on internal lanes
//
// Revision 1.6  2003/06/18 11:31:49  dkrajzew
// some functions commented out or unneeded debug outputs removed
//
// Revision 1.5  2003/05/20 09:31:46  dkrajzew
// emission debugged; movement model reimplemented (seems ok); detector output debugged; setting and retrieval of some parameter added
//
// Revision 1.4  2003/04/14 08:33:00  dkrajzew
// some further bugs removed
//
// Revision 1.3  2003/02/07 10:41:50  dkrajzew
// updated
//
// Revision 1.2  2002/10/16 16:42:29  dkrajzew
// complete deletion within destructors implemented; clear-operator added for container; global file include; junction extended by position information (should be revalidated later)
//
// Revision 1.1  2002/10/16 14:48:26  dkrajzew
// ROOT/sumo moved to ROOT/src
//
// Revision 1.2  2002/04/18 10:51:22  croessel
// Introduced new method "bool driveRequest()" in class DriveBrakeRequest
// to let findCompetitor check, if a first car set a request.
//
// Revision 1.1.1.1  2002/04/08 07:21:23  traffic
// new project name
//
// Revision 2.0  2002/02/14 14:43:17  croessel
// Bringing all files to revision 2.0. This is just cosmetics.
//
// Revision 1.5  2002/02/05 13:51:52  croessel
// GPL-Notice included.
// In *.cpp files also config.h included.
//
// Revision 1.4  2002/01/31 13:51:40  croessel
// Revision 1.3 Log-message corrected.
//
// Revision 1.3  2002/01/30 16:16:43  croessel
// Destructor defined.
//
// Revision 1.2  2001/12/20 14:30:23  croessel
// using namespace std added.
//
// Revision 1.1  2001/12/13 15:56:47  croessel
// Initial commit.
//
/* =========================================================================
 * included modules
 * ======================================================================= */
#ifdef HAVE_CONFIG_H
#ifdef WIN32
#include <windows_config.h>
#else
#include <config.h>
#endif
#endif // HAVE_CONFIG_H

#include "MSLinkCont.h"
#include "MSLogicJunction.h"
#include "MSLane.h"
#include "MSInternalLane.h"

#ifdef _DEBUG
#include <utils/dev/debug_new.h>
#endif // _DEBUG


/* =========================================================================
 * used namespaces
 * ======================================================================= */
using namespace std;


/* =========================================================================
 * member method definitions
 * ======================================================================= */
/* -------------------------------------------------------------------------
 * methods from MSLogicJunction
 * ----------------------------------------------------------------------- */
MSLogicJunction::MSLogicJunction(string id, const Position2D &position,
                                 LaneCont incoming
#ifdef HAVE_INTERNAL_LANES
                                 , LaneCont internal
#endif
                                 )
    : MSJunction( id, position ),
    myIncomingLanes(incoming),
#ifdef HAVE_INTERNAL_LANES
    myInternalLanes(internal),
#endif
    myRequest(false), myInnerState(false), myRespond(false)
{
}

//-------------------------------------------------------------------------//

MSLogicJunction::~MSLogicJunction()
{
}

//-------------------------------------------------------------------------//

void
MSLogicJunction::postloadInit()
{
    /*
    if(getID()=="1565") {
        int bla = 0;
    }
    // inform links where they have to report approaching vehicles to
    size_t requestPos = 0;
    LaneCont::iterator i;
    // going through the incoming lanes...
    for(i=myIncomingLanes.begin(); i!=myIncomingLanes.end(); i++) {
        const MSLinkCont &links = (*i)->getLinkCont();
        // ... set information for every link
        for(MSLinkCont::const_iterator j=links.begin(); j!=links.end(); j++) {
            (*j)->setRequestInformation(&myRequest, requestPos,
                &myRespond, requestPos/, clearInfo/);
            requestPos++;
        }
    }
#ifdef HAVE_INTERNAL_LANES
    // set information for the internal lanes
    requestPos = 0;
    for(i=myInternalLanes.begin(); i!=myInternalLanes.end(); i++) {
        // ... set information about participation
        static_cast<MSInternalLane*>(*i)->setParentJunctionInformation(
            &myInnerState, requestPos++);
    }
#endif
    */
}


/**************** DO NOT DEFINE ANYTHING AFTER THE INCLUDE *****************/

// Local Variables:
// mode:C++
// End:
