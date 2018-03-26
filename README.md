## OPC UA Modeling eXcelerator (UMX)

UMX is a tool for OPC UA developers to create Infromation Models to generate OPC UA compliant Nodesets for use in OPC UA Servers.

We maintain a set of compiled setup binaries on our website at https://beeond.net/

Its models are saved into ModelDesign compliant XML files and can be compiled to generate UANodeset files.

For more information on ModelDesign and Nodeset files, please visit https://github.com/OPCFoundation/UA-ModelCompiler

To learn how to develop OPC UA applications, consider registering for our official trainings at https://beeond.net/opc-ua-developer-training/



### Buiding instructions
#### Linux (Note that umx did not undergo intensive testing in linux.) :
  - Install the required libraries.

    - Build wxWidgets (For more options/details on the compilation: https://wiki.wxwidgets.org/Compiling_and_getting_started)
      - Download wxWidgets 3.1.1 source code for linux https://www.wxwidgets.org/downloads/      
      - cd wxWidgets-3.1.1 (Change path to where the compressed file was extracted.)
      - mkdir gtk-build
      - cd gtk-build
      - ../configure
      - make
      - make install  (sudo or su to allow installation)

    - Install xsd
      - Download xsd 4.0 synthesis for linux http://www.codesynthesis.com/products/xsd/download.xhtml
      - rpm -ivh xsd-4.0.0-1.i686.rpm

    - Build xerces
      - Download xerces 3.2 for linux http://xerces.apache.org/xerces-c/download.cgi
      - cd xerces-c-3.2.0 (Change path to where the compressed file was extracted.)
      - ./configure
      - make
      - make install  (sudo or su to allow installation)

  - Compile umx
    - cd to the umx directory cloned from git
    - copy _Make.linux.properties Make.linux.properties (Copy the user sample template for linux Makefile include)
    - Configure/Edit the Makefile.linux.properties. Property values vary depending on the installation paths of the required libraries.
    - make
  
  - Run umx
    - ./eXcelerator

#### Windows:
  - Install the required libraries.

    - Download and install MinGW-w64(mingw-w64-install.exe)  https://sourceforge.net/projects/mingw-w64/files/latest/download?source=files
      - Run the installer and choose version 7.2

    - Build wxWidgets (For more options/details on the compilation: https://wiki.wxwidgets.org/Compiling_and_getting_started)
      - Download wxWidgets 3.1.1 source code for windows https://www.wxwidgets.org/downloads/
      - Open MinGW-w64 "Run Terminal" (There shoud be a shortcut in the Programs/Apps created from the installation.)
        - cd wxwidgets3.1.1\build\msw
        - mingw32-make -f makefile.gcc SHARED=1 UNICODE=1 BUILD=release clean
        - mingw32-make -f makefile.gcc SHARED=1 UNICODE=1 BUILD=release

    - Download xerces files and extract. https://sourceforge.net/projects/mingw/files/MinGW/Contributed/xerces-c/xerces-c-3.1.2
      - xerces-c-3.1.2-mingw32-4.9.3-dll-3.tar 
      - xerces-c-3.1.2-mingw32-4.9.3-dev.tar

    - Download xsd file and extract. https://www.codesynthesis.com/products/xsd/download.xhtml
      - xsd-4.0.0-i686-windows.zip
  
  - Compile umx
    - Open MinGW-w64 "Run Terminal" (There shoud be a shortcut in the Programs/Apps created from the installation.)
      - cd to the umx directory cloned from git
      - cp _Make.windows.properties Make.windows.properties (Copy the user sample template for windows Makefile include)
      - Configure/Edit the Makefile.windows.properties. Property values vary depending on the installation paths of the required libraries.
      - mingw32-make

  - Run (Put this in a batch file.)
    - set PATH=%PATH%;<PATH_EXTRACTED>\wxWidgets-3.1.1\lib\gcc_dll;<PATH_EXTRACTED>\xerces-c-3.1.2-mingw32-4.9.3-dll-3\bin;<PATH_INSTALLED>\mingw-w64\i686-7.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin
    - eXcelerator.exe

### Development
  - Always use Code::Blocks wxSmith to modify the UI for ease of UI maintenance and modification.
  - TODO: Add notes on the changes of the opc schema ModelDesign element complex type reordering of the children.

### TODO/Nice to have
* Rebuild xsd synthesis ModelDesign schema with std=c++11 so we can get rid of the deprecated auto_ptr and replace it with shared_ptr.
* Update those UI dialogs and panels (e.g. wxProjectDialog, wxAbout) that are not using layout. We want to have a consistent UI across platforms.
* Convert to CMake.
* Add a layer of classes to the node elements so we can replace all the 'if' clause with polymorphic calls.
* Add a new attribute to the opc schema e.g. access=readonly . This will replace the StringId hack.
* If we can just determine the prefix from the element, we would not need to use the StringId attribute workaround.
This may be a potential issue in the future if StringId attribute is added to the wxNodePanel.
* Remove wx prefixes of the UI classes(wxNodePanel to just PanelNode) to avoid the notion that this is part of the wxWidget core classes.
* Add/Edit/Delete namespaces in the Project Setting dialog.
* Revisit the logic for assigning a prefix on a new element created from a BaseType. Not solid.
* Modify the Makefile to detect header changes.

<br>
<br>
<br>
<br>