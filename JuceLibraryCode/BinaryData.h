/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   background_jpg;
    const int            background_jpgSize = 57413;

    extern const char*   background_png;
    const int            background_pngSize = 570392;

    extern const char*   faderView2_png;
    const int            faderView2_pngSize = 43408;

    extern const char*   faderView_png;
    const int            faderView_pngSize = 69943;

    extern const char*   knob_AR_png;
    const int            knob_AR_pngSize = 918188;

    extern const char*   knob_T_png;
    const int            knob_T_pngSize = 922488;

    extern const char*   knob_input_png;
    const int            knob_input_pngSize = 1327618;

    extern const char*   knob_output_png;
    const int            knob_output_pngSize = 1220060;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
