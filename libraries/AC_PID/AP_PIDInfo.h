#pragma once

// This structure provides information on the internal member data of
// a PID.  It provides an abstract way to pass PID information around,
// useful for logging and sending mavlink messages.

// It is also used to pass PID information into controllers...

struct AP_PIDInfo {
    float target{0.0f};
    float actual{0.0f};
    float error{0.0f};
    float P{0.0f};
    float I{0.0f};
    float D{0.0f};
    float FF{0.0f};
    float DFF{0.0f};
    float Dmod{0.0f};
    float slew_rate{0.0f};
    bool limit{false};
    bool PD_limit{false};
    bool reset{false};
    bool I_term_set{false};
};
