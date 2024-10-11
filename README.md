<!--
  Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
  See https://llvm.org/LICENSE.txt for license information.
  SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
-->

> [!IMPORTANT]
>
> The Quantum Device Management Interface (QDMI) is experimental at this stage, and significant
> changes, including breaking changes, are anticipated in upcoming releases.

![QDMI](docs/_static/qdmi.png)

# QDMI — Quantum Device Management Interface (QDMI)

<!-- [DOXYGEN] -->

The Quantum Device Management Interface (QDMI) is the central part of the Munich Quantum Software
Stack (MQSS)—a sophisticated software stack to connect end users to the wide range of possible
quantum backends. It enables the submission to and the control of gate-based quantum systems and
enables software tools to automatically retrieve and adapt to changing physical characteristics and
constraints of different platforms. QDMI strives to connect the software and hardware developers,
mediating between their competing interests, bridging between technologies, and eventually providing
corresponding figures of merits and constraints to be considered. QDMI is therefore the method of
choice for integrating new platforms into the MQSS and for software tools to query information from
these platforms. QDMI is provided as a C header file to allow fast integration into an HPC
environment and consists of four main components:

- **QDMI Core**: Provides core functionality to manage sessions as well as to open and close
  connections to devices.
- **QDMI Control**: Enables the control of the quantum devices. One can submit quantum circuits,
  control the job queue, and readout measurement results.
- **QDMI Device**: Provides device handling functionality, like initiating the calibration or
  checking the status of the device.
- **QDMI Query**: Allows querying properties of the device, e.g., supported gates, error rates, gate
  duration, etc.

<!-- [DOXYGEN] -->

<p align="center">
  <a href="https://mqss.readthedocs.io/projects/qdmi">
  <img width=30% src="https://img.shields.io/badge/documentation-blue?style=for-the-badge&logo=read%20the%20docs" alt="Documentation" />
  </a>
</p>

> [!IMPORTANT]
>
> The Quantum Device Management Interface (QDMI) is in an active development phase. Our development
> process is open to the community, encouraging contributions and feedback. Please be aware that
> QDMI is experimental at this stage, and significant changes, including breaking changes, are
> anticipated in upcoming releases. We value your input and invite you to participate in shaping
> QDMI's future. For the latest updates and to contribute, visit our
> [issues page](https://github.com/Munich-Quantum-Software-Stack/QDMI/issues).

## Contact

The development of this project is led by [Laura Schulz](mailto:laura.schulz@lrz.de) (LRZ),
[Martin Schulz](mailto:martin.w.j.schulz@tum.de) (TUM CAPS), as well as
[Robert Will](mailto:robert.wille@tum.de) (TUM CDA) on the management side and
[Lukas Burgholzer](mailto:lukas.burgholzer@tum.de) (TUM CDA) as well as
[Jorge Echavarria](mailto:jorge.echavarria@lrz.de) (LRZ) from the technical side.

Please try to use the publicly accessible GitHub channels
([issues](https://github.com/Munich-Quantum-Software-Stack/QDMI/issues),
[discussions](https://github.com/Munich-Quantum-Software-Stack/QDMI/discussions),
[pull requests](https://github.com/Munich-Quantum-Software-Stack/QDMI/pulls)) to allow for a
transparent and open discussion as much as possible.
