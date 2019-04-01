# CRTTime for Intel and ARM Processors ReadMe

__Current Version:__ 1.0.0.3

__Release Date:__ Sunday, 31 March 2019

The purpose of this repository is to publish a port of a very simple library
that wraps the CRT functions for getting and formatting the time from the
system clock in a friendly standard DLL that makes these useful routines
readily accessible to fans of most programming languages, even VBA. If your
language or tool can call into the Windows API, it can call into this library.

This code is entirely of my own devising, although most of it is not especially
original or interesting. The feature that make it worthy of publication is that
the Visual Studio project around which it is built supports building it for four
platforms.

1. __Win32__ runs in 32-bit mode on Intel and AMD processors.
2. __x64__ runs in 64-bit mode on Intel and AMD processors.
3. __ARM__ runs in 32-bit mode on any ARM processor.
4. __ARM64__ runs in 64-bit mode on any ARM processor.

The unit test program displays a message indicating the platform on which it is
executing.

## Using These Libraries

If you have any edition of Visual Studio 2017 installed on a 64-bit copy of
Microsoft Windows, and you intend to use only the 64-bit Intel libraries, you
may skip the rest of this section, because the required runtime libraries are
already installed.

Otherwise, please keep reading, especially if your target is an ARM processor,
since the Microsoft C runtime for ARM is tucked away, and finding them took
many searches, spread across about a week, to find a proper package. Moreover,
extracting them from that package requires some specialized knowledge about the
internal format of a NuGet package.

For your convenience, the required CRT libraries are included in the binary
packages, and the build scripts deposit a copy into the output directory of each
project.

## ToDo

Though the project contains two source modules, `AbbreviateTZNameA.C` and
`AbbreviateTZNameW.C,` intended to implement substitution of abbreviations for
the time zone names returned by strftime, both are stubs, neither of which is
wired into the library.

Strings are currently hard coded, though embedding them as string resources
would slightly reduce the size on disk and in memory of the DLL. There is, of
course, a tad of computational overhead involved in moving the strings into
Win32 resource strings, but doing so would pave the way for translations to
support other written languages.

## The Visual Studio Solution and Projects

These projects are organized in a fairly conventional manner. Four directories
off the main solution directory contain the output files that target the named
platform. Within each directory are the output (`.dll`, `.exp`, `.exe`, `.map`,
`.lib`, and `.pdb`) files.

Within each project directory, a like-named directory holds the intermediate
outputs (`.asm` and `.obj`) are in the `Intermediate` subdirectory.

There are two projects

1. __CRTTime__ contains the source code of the library, itself.

2. __CRTTime_UnitTests__ contains the source code of the unit test program, which
   is a normal program; I didn't use a "unit test framework" because I believe it
   is overkill for such a simple project.

The Visual Studio projects specify the settings that are required to guarantee
that certain required settings have the correct values for a successful build.
For your convenience, these required values are set forth in the following table.

| Target          | Property Name                 | Project           | Property Value                      |
|-----------------|-------------------------------|-------------------|-------------------------------------|
| ClCompile       | AdditionalIncludeDirectories  | All               | ..\..\..;..\..\masmx86;             |
| ClCompile       | PreprocessorDefinitions       | All               | WIN32;\_DEBUG;CRTTIME_EXPORTS;      |
|                 |                               |                   | \_WINDOWS;\_USRDLL                  |
| ClCompile       | PrecompiledHeader             | All               | NotUsing                            |
| ClCompile       | OmitFramePointers             | All               | false                               |
| Link            | AdditionalDependencies        | CRTTime_UnitTests | $(ProjectDir)..\LIB\$(Platform)     |
|                 |                               |                   |     \$(Configuration)               |
|                 |                               |                   |     \NativeConssoleAppAids          |
|                 |                               |                   |     $(PlatformArchitecture).lib;    |
|                 |                               |                   |     $(ProjectDir)..\$(Platform)     |
|                 |                               |                   |     \$(Configuration)               |
|                 |                               |                   |     \CRTTime                        |
|                 |                               |                   |     $(PlatformArchitecture).lib     |
| Link            | OutputFile                    | All               | $(OutDir)$(ProjectName)$(TargetExt) |
| Link            | ImageHasSafeExceptionHandlers | All Win32         | true                                |
| Link            | ImageHasSafeExceptionHandlers | All Others        | false                               |

Macro `$(WWLinkLibPath)`, mentioned in `AdditionalLibraryDirectories`, and
`$(WWIncludePath)`, mentioned in `AdditionalIncludeDirectories`, refer to user
environment variables that won't exist in your installation. Hence, both will
expand to empty strings, causing them to be harlessly and silently eliminated.

## Getting the CRT Libraries: The Gory Details

To use these libraries on any supported platform, you must acquire and install
the Microsoft« C Runtime Library, version 14.00.24234.1 or later, called
`vcruntime140.dll` on all platforms. Microsoft distributes it as part of the
"Microsoft Visual C++ 2015 Redistributable Update 3 RC" package, available from
<https://www.microsoft.com/en-us/download/details.aspx?id=52685> for Intel and
AMD CPUs, and from <https://dotnet.myget.org/F/dotnet-core/api/v2/package/vc-runtime/2.0.0/>
for ARM processors.

- The __Intel/AMD__ packages come as self-extracting `EXE` files, one each for
__x86__ (32 bits) and __x64__ (64 bits), which correspond to the __Win32__ and
__x64__ configurations, respectively, in the Visual Studio project configuration
files. Though they are packaged separately, the download page offers the option
of fetching both in one pass. If you take that option, you should elect to
__dwonload__ both, then view the packages in your `Downloads` folder. This
suggestion applies to Edge and Chrome for certain, and is sound advice for other
Web browsers. Though technically self-extracting archives, manually extracting
them makes clear that they are intended to be executed, so that the executable
code embedded therein can reassemble the numerous bits into a handful of program
files before it installs them.

- The __ARM__ package comes as a `.nupkg` that can be renamed to `.zip`, and
treated as an ordinary ZIP archive. Both __ARM__ and __ARM64__ (32 and 64 bit)
runtimes come in one package. To get the goods, extract the archive into a new
directory, and use the file explorer to drill down into it. Inside directory
`content\VC\Redist\MSVC\14.14.26405\onecore` are two subdirectories, helpfully
named `arm` and `arm64`. Unlike the Intel/AMD packages, the __ARM__ package is
a straightforward, if opaque, ZIP archive, and the contents of the two leaf
directories need only to be copied into a directory that is in your __PATH__
list, and they are ready for use.

For those who are interested, the directory structure in the NuGet package
reflects the location into which the files are installed into Visual Studio
when you install the ARM compilers and tools.

To get the tools for Microsoft Visual Studio, start the __Visual Studio Installer__,
which should be on the main list of __Programs__ (not APPs), answer the UAC
prompt, and select the __Modify__ button. Once the form draws itself, select the
__Individual Components__ tab, and scroll down almost to the bottom, where you
will eventually find __Visual C++ compilers and libraries for ARM and ARM64__,
listed as two items. Still further down, you will find packages for __ATL__ and
__MFC__, which you will need if the code you plan to port uses either. Check
the packages you want, and click __Modify__. When the installer is done, you are
ready to go.