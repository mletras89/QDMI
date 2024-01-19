include(FetchContent)

FetchContent_Declare(
    qinfo
    GIT_REPOSITORY git@github.com:Munich-Quantum-Software-Stack/QInfo.git
    GIT_TAG main  # Replace with the desired branch, tag, or commit
)

FetchContent_MakeAvailable(qinfo)
