#pragma once

class Wildcard {
 public:
    /**
     * Compares two Wildcard objects.
     *
     * @param other Second Wildcard object to be compared against.
     * @return Returns true if both Wildcard objects are the same, false otherwise.
     */
    bool operator==(const Wildcard &other) const;
};
