# Exercise Strong Types

## U = R * I - simple Ohm's law

Implement strong types for voltage, resistance and current and define the required operations. Write tests for the basic operations required.

```C++
ASSERT_EQUAL(500._Ohm, 5._V / 0.01_A);
```

Define UDL (user-defined-literals) suffixes for `_Ohm`, `_V`, `_A`. You might need to define overloads of the UDL operators for `unsigned long long` and `long double`

You can do everything yourself or employ my strong type framework PSSST ([https://github.com/PeterSommerlad/PSsst](https://github.com/PeterSommerlad/PSsst)). Just copy the pssst.h file into your project ([https://raw.githubusercontent.com/PeterSommerlad/PSsst/Trunk/pssst.h](https://raw.githubusercontent.com/PeterSommerlad/PSsst/Trunk/pssst.h)).

Compare your strong type approach with what is available (i just found it googling) at
[https://geant4.web.cern.ch/sites/default/files/geant4/collaboration/working_groups/electromagnetic/gallery/units/SystemOfUnits.html](https://geant4.web.cern.ch/sites/default/files/geant4/collaboration/working_groups/electromagnetic/gallery/units/SystemOfUnits.html)

Or look at [https://gitlab.cern.ch/CLHEP/CLHEP/-/blob/c2b1df2bb89679cc5f3af42fa361e066f2ef4a6c/Units/Units/SystemOfUnits.h](https://gitlab.cern.ch/CLHEP/CLHEP/-/blob/c2b1df2bb89679cc5f3af42fa361e066f2ef4a6c/Units/Units/SystemOfUnits.h) and discuss if that is a beneficial system for representing SI units?