#include "MacFunctions.hpp"

#include <cstdio>
#include <stdexcept>

#include <sys/types.h>
#include <sys/sysctl.h>
#include <CoreFoundation/CoreFoundation.h>

#include <signal.h>
#include <stdarg.h>

bool canUseSSE2() {
    size_t buflen = 512;
    char buf[buflen];

    if (sysctlbyname("machdep.cpu.features", &buf, &buflen, NULL, 0) < 0) {
        std::perror("sysctl broke");
        return false;
    }

    return (strstr(buf, "SSE2") != NULL);
}

// Icons to decorate the dialog message box.
// Use `Icon::None` for no icon decoration.
struct Icon {
    enum Enum {
        None,
        Information,
        Warning,
        Error
    };
};

// Buttons present in the dialog message box.
// The clicked button is returned by `showMessageBox()`.
// These can be combined as flags in the `buttons` parameter.
struct Button {
    enum Enum {
        Ok     = 1 << 0, // Has an OK/Accept button
        Cancel = 1 << 1  // Has a Cancel button
    };
};

static Button::Enum showMessageBox(Icon::Enum icon, unsigned int buttons, const char* title, const char* message) {
    // Icon::None
    CFOptionFlags cfAlertIcon = kCFUserNotificationPlainAlertLevel;

    // Convert strings to CF strings:
    CFStringRef cfStrDefaultButton   = CFSTR("OK");    
    CFStringRef cfStrHeader  = CFStringCreateWithCString(kCFAllocatorDefault, title,   kCFStringEncodingUTF8);
    CFStringRef cfStrMessage = CFStringCreateWithCString(kCFAllocatorDefault, message, kCFStringEncodingUTF8);

    // Launch the message box, blocking the current thread
    // until the user click a button or closes the dialog.
    CFOptionFlags result;
    CFUserNotificationDisplayAlert(
        0,                    // No timeout
        cfAlertIcon,          // Icon of the message box
        nullptr,              // Icon URL if loading from web
        nullptr,              // Second URL ???
        nullptr,              // Localized strings
        cfStrHeader,          // Header text
        cfStrMessage,         // Message text
        cfStrDefaultButton,   // Default button
        nullptr,              // Second button, null -> no other button
        nullptr,              // Third button
        &result               // Response flags
    );

    CFRelease(cfStrHeader);
    CFRelease(cfStrMessage);

    if (result == kCFUserNotificationDefaultResponse) {
        return Button::Ok;
    }

    // kCFUserNotificationAlternateResponse, shouldn't happen.
    return Button::Cancel;
}

int MessageBoxA(int ownerWindow, const char* message, const char* title, unsigned int flags) {
    if (ownerWindow != 0) {
        throw std::invalid_argument("Mac implementation of MessageBoxA doesn't support owner windows.");
    }

    if (flags != MB_OK) {
        throw std::invalid_argument("Mac implementation of MessageBoxA doesn't support other flags than MB_OK.");
    }

    if (title == nullptr) {
        title = "Error";
    }

    return showMessageBox(Icon::None, Button::Ok, title, message);
}

void __debugbreak() {
	raise(SIGTRAP);
}

int _snprintf_s(char* buffer, size_t buflen, size_t count, const char* format, ...) {
	if ((count != _TRUNCATE) && (count < buflen)) {
        buflen = count;
    }

    va_list ap;

    va_start(ap, format);
    int retval = vsnprintf(buffer, buflen, format, ap);
    va_end(ap);

    if ((retval >= 0) && (buflen <= static_cast<size_t>(retval))) {
        retval = -1;
    }

    return retval;
}
