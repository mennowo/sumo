#ifndef MSJunction_H
#define MSJunction_H
/***************************************************************************
                          MSJunction.h  -  Base class for all kinds of
                                           junctions.
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

// $Log$
// Revision 1.10  2004/11/23 10:20:09  dkrajzew
// new detectors and tls usage applied; debugging
//
// Revision 1.9  2004/08/02 12:09:39  dkrajzew
// using Position2D instead of two doubles
//
// Revision 1.8  2003/11/11 08:38:51  dkrajzew
// consequent position2D instead of two doubles added
//
// Revision 1.7  2003/07/30 09:02:01  dkrajzew
// comments corrigued
//
// Revision 1.6  2003/07/22 15:05:22  dkrajzew
// warnings removed; formatted the code
//
// Revision 1.5  2003/07/16 15:31:14  dkrajzew
// junctions are now able to build gui-wrappers (throws an exception within the gui-version, but the interface is needed)
//
// Revision 1.4  2003/07/07 08:16:28  dkrajzew
// a junction is now able to return its id
//
// Revision 1.3  2003/02/07 10:41:51  dkrajzew
// updated
//
// Revision 1.2  2002/10/16 16:42:28  dkrajzew
// complete deletion within destructors implemented; clear-operator added for container; global file include; junction extended by position information (should be revalidated later)
//
// Revision 1.1  2002/10/16 14:48:26  dkrajzew
// ROOT/sumo moved to ROOT/src
//
// Revision 1.1.1.1  2002/04/08 07:21:23  traffic
// new project name
//
// Revision 2.0  2002/02/14 14:43:15  croessel
// Bringing all files to revision 2.0. This is just cosmetics.
//
// Revision 1.14  2002/02/01 11:40:34  croessel
// Changed return-type of some void methods used in for_each-loops to
// bool in order to please MSVC++.
//
// Revision 1.13  2001/12/20 11:54:05  croessel
// using namespace std replaced by std::
//
// Revision 1.12  2001/12/12 17:46:01  croessel
// Initial commit. Part of a new junction hierarchy.
//
/* =========================================================================
 * compiler pragmas
 * ======================================================================= */
#pragma warning(disable: 4786)


/* =========================================================================
 * included modules
 * ======================================================================= */
#include <string>
#include <vector>
#include <map>
#include <utils/geom/Position2D.h>


 /* =========================================================================
 * class declarations
 * ======================================================================= */
class GUIJunctionWrapper;
class GUIGlObjectStorage;


/* =========================================================================
 * class definitions
 * ======================================================================= */
/**
 */
class MSJunction
{
public:
    /// needed for the access to the dictionary
    friend class GUIEdgeGrid;

    /// Destructor.
    virtual ~MSJunction();

    /** Use this constructor only. */
    MSJunction( std::string id, const Position2D &position );

    /** performs some initialisation after the loading
        (e.g., link map computation) */
    virtual void postloadInit();

    /** Clears junction's and lane's requests to prepare for the next
        iteration. */
    virtual bool clearRequests() = 0;

    /// Sets the responds
    virtual bool setAllowed() = 0;

    /** @brief Inserts MSJunction into the static dictionary
        Returns true if the key id isn't already in the dictionary.
        Otherwise returns false (the junction is not inserted then). */
    static bool dictionary( std::string id, MSJunction* junction);

    /** @brief Returns the MSEdgeControl associated to the key id if exists,
        Otherwise returns 0. */
    static MSJunction* dictionary( std::string id);

    static size_t dictSize();

    /** Returns the list of all known junctions */
    static std::vector<std::string> getNames();

    /** Clears the dictionary */
    static void clear();

    /** @brief Performs some initialisation after the net was completely loaded
        This is done for all junctions within the dictionary */
    static void postloadInitContainer();

    /** returns the junction's position */
    const Position2D &getPosition() const;

    /// Returns the id of the junction
    std::string id() const;

    // valid for gui-version only
    virtual GUIJunctionWrapper *buildJunctionWrapper(
        GUIGlObjectStorage &idStorage);

    friend class GUIGridBuilder;

protected:
    /// unique ID
    std::string myID;

    /// definition of the static dictionary type
    typedef std::map< std::string, MSJunction* > DictType;

    /** Static dictionary to associate string-ids with objects. */
    static DictType myDict;

    /** the position */
    Position2D myPosition;

private:
    /// Default constructor.
    MSJunction();

    /// Copy constructor.
    MSJunction( const MSJunction& );

    /// Assignment operator.
    MSJunction& operator=( const MSJunction& );

};

/**************** DO NOT DECLARE ANYTHING AFTER THE INCLUDE ****************/

#endif

// Local Variables:
// mode:C++
// End:
