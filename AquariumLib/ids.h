/**
 * @file ids.h
 * @author James G
 *
 * ID values for this program
 */
 
#ifndef IDS_H
#define IDS_H

/**
 * Enum of IDs to use for command menu event handling.
 * Each ID is 1 higher than highest wxID value.
 */
enum IDs
{
    IDM_ADDFISHBETA = wxID_HIGHEST + 1,
    IDM_ADDFISHBUBBLES,
    IDM_ADDFISHSPARTY,
    IDM_ADDDECORCASTLE
};

#endif //IDS_H
