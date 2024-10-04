# FAQ

## What is MQSS?

**MQSS** stands for _Munich Quantum Software Stack_, which is a project of the _Munich Quantum
Valley (MQV)_ initiative and is jointly developed by the _Leibniz Supercomputing Centre (LRZ)_ and
the Chairs for _Design Automation (CDA)_, and for _Computer Architecture and Parallel Systems
(CAPS)_ at TUM. It provides a comprehensive compilation and runtime infrastructure for on-premise
and remote quantum devices, support for modern compilation and optimization techniques, and enables
both current and future high-level abstractions for quantum programming. This stack is designed to
be capable of deployment in a variety of scenarios via flexible configuration options, including
stand-alone scenarios for individual systems, cloud access to a variety of backends as well as tight
integration into HPC environments supporting quantum acceleration. Within the MQV, a concrete
instance of the MQSS is deployed at the LRZ for the MQV, serving as a single access point to all of
its quantum devices via multiple compatible access paths, including a web portal, command line
access via web credentials as well as the option for hybrid access with tight integration with LRZ's
HPC systems. It facilitates the connection between end-users and quantum computing platforms by its
integration within HPC infrastructures, such as those found at the LRZ.

## What is QDMI?

**QDMI**, or _Quantum Device Management Interface_, serves as the communication interface between
software within the MQSS and the quantum hardware connected to the MQSS. The aim is to provide a
standard way to communicate with quantum resources that can be widely used by the whole quantum
community.

## Who is using QDMI?

QDMI will be the default communication channel within the MQSS, meaning all hardware and software
tools integrated into the MQSS will have to support QDMI. Moreover, platforms implementing QDMI can
also be seamlessly integrated in other software stacks understanding QDMI, as can software tools
interfacing with QDMI for platform feedback.

## Where is the code?

The code is publicly available hosted on GitHub at
[github.com/Munich-Quantum-Software-Stack/QDMI](https://github.com/Munich-Quantum-Software-Stack/QDMI).

## Under which license is QDMI released?

QDMI is released under the Apache License v2.0 with LLVM Exceptions. See [LICENSE](../LICENSE) for
more information. Any contribution to the project is assumed to be under the same license.

## Why is it written in C and not in Python?

The interface is written in C to allow close integration within the MQSS and fulfill the performance
as well as stability requirements needed for production systems, in particular as we scale quantum
systems. Further, this enables a clean integration into existing and well-established system
software stacks, including those for HPC.

## Can I still integrate my Python code?

Python natively allows calling C APIs. So while it might not be as straightforward as the usage from
C/C++, it is definitely possible. However, we generally do expect Python-based programming
approaches to be used as front-ends, feeding into a natively implemented compiler infrastructure,
which then relies on QDMI. This is very analog on how Python is used in many other parts of
high-performance computing.
