/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_27870617_INCLUDED
#define BINARYDATA_H_27870617_INCLUDED

namespace BinaryData
{
    extern const char*   BlackKnob_png;
    const int            BlackKnob_pngSize = 1774677;

    extern const char*   MTIID_png;
    const int            MTIID_pngSize = 3101;

    extern const char*   MumuLight_png;
    const int            MumuLight_pngSize = 3640;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
