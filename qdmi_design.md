# QDMI

## Classes

### Session

- Name: `QDMI_Session`
- Description: Class for managing individual sessions
- Members:
  - `QInfo info`: Additional/Optional information of the session
- Methos:
  - `int QDMI_Session_create(QInfo info, QDMI_Session* session)`:

### Device

- Name: `QDMI_Device`
- Description: Main class representing a quantum device
- Members:- 
  - `char* name`: Name of the device
  - `QInfo info`: Additional/Optional information of the session
### Site

- Name: `QDMI_Site`
- Description:
- Members:
  - `QInfo info`: Additional/Optional information of the session


### Operation

- Name: `QDMI_Operation`
- Description:
- Members:
  - `QInfo info`: Additional/Optional information of the session 
