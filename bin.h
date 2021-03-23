/* SPDX-License-Identifier: LGPL-3.0-or-later */

/** @file
 * @brief Provide binary class
 *
 * @author Erez Geva <ErezGeva2@@gmail.com>
 * @copyright 2021 Erez Geva
 *
 */

#ifndef __BUF_H
#define __BUF_H

#include <string>
#include <stdint.h>
#include <cstring>

const size_t EUI48 = 6; /**< 48 bits MAC address length */
const size_t EUI64 = 8; /**< 64 bits MAC address length */

/**
 * @brief hold a binary octets
 * @note functions returning std::string for readable strings
 */
class binary
{
  private:
    std::string m_str;
  public:
    binary() {}
    /**
     * Copy constructor
     * @param[in] other object
     */
    binary(const binary &other) { m_str = other.m_str; }
    /**
     * Constructor from buffer
     * @param[in] buf pointer to binary octets
     * @param[in] length
     */
    binary(const void *buf, const size_t length) { set(buf, length); }
    /**
     * Constructor buffer with fixed length
     * @param[in] length of buffer
     * @param[in] set value to set all octests
     */
    binary(const size_t length, uint8_t set = 0) { m_str.resize(length, set); }
    /**
     * Get binary length
     * @return binary length
     */
    size_t length() const { return m_str.length(); }
    /**
     * Get binary length
     * @return binary length
     */
    size_t size() const { return m_str.length(); }
    /**
     * Return if binary is empty
     * @return treu if empty
     */
    bool empty() const { return m_str.empty(); }
    /**
     * Get pointer to binary
     * @return pointer to octets
     */
    const uint8_t *get() const {return (const uint8_t *)m_str.c_str();}
    /**
     * Set new value
     * @param[in] buf pointer to binary octets
     * @param[in] length
     * @return reference to itself
     */
    binary &set(const void *buf, const size_t length) {
        m_str = std::string((const char *)buf, length);
        return *this;
    }
    /**
     * Set value in position
     * @param[in] position in binary octets
     * @param[in] value to set in positions
     * @return reference to itself
     * @note resize the binary as needed
     */
    binary &set(const size_t position, const uint8_t value) {
        if(position >= length())
            resize(position + 1);
        m_str[position] = value;
        return *this;
    }
    /**
     * Resize buffer
     * @param[in] length new length
     */
    binary &resize(const size_t length) { m_str.resize(length); return *this; }
    /**
     * Copy binary to target memory block
     * @param[in, out] target memory block
     */
    void copy(uint8_t *target) const { memcpy(target, get(), length()); }
    /**
     * Append single octet using operator +=
     * @param[in] add octet to add
     * @return reference to itself
     */
    binary &operator += (const uint8_t add) {
        m_str.append(1, add);
        return *this;
    }
    /**
     * Append single octet
     * @param[in] add octet to add
     * @return reference to itself
     */
    binary &append(const uint8_t add) {
        m_str.append(1, add);
        return *this;
    }
    /**
     * append octetes using operator +=
     * @param[in] other binary to add
     * @return reference to itself
     */
    binary &operator += (const binary &other) {
        m_str += other.m_str;
        return *this;
    }
    /**
     * append octetes
     * @param[in] other binary to add
     * @return reference to itself
     */
    binary &append(const binary &other) {
        m_str += other.m_str;
        return *this;
    }
    /**
     * Convert IP address to string
     * @return Ip address
     * @note Support both IP version 4 and 6
     * @note the user should use with binary IP address
     *  the calss does not verify
     */
    std::string toIp() const;
    /**
     * Convert IP address string to binary
     * @param[in] string address
     * @return true if valid IP address version 4 or 6
     * @note this function will toss old value
     */
    bool fromIp(const std::string string);
    /**
     * Convert IP address string to binary
     * @param[in] string address
     * @param[in] domain of IP to use
     * @return true if valid IP address version 4 or 6
     * @note this function will toss old value
     */
    bool fromIp(const std::string string, int domain);
    /**
     * Convert ID address to string
     * @return address
     * @note Support MAC addresses
     */
    std::string toId() const { return bufToId((uint8_t *)m_str.c_str(), length()); }
    /**
     * Convert binary ID to string
     * @param[in] id pointer to memory buffer
     * @param[in] length of memory buffer
     * @return address
     * @note Support MAC addresses
     */
    static std::string bufToId(const uint8_t *id, size_t length);
    /**
     * Convert ID address string to binary
     * @param[in] string address
     * @return true if valid ID address
     * @note Support MAC addresses
     */
    bool fromId(const std::string string);
    /**
     * Convert MAC address string to binary
     * @param[in] string address
     * @return true if MAC address
     */
    bool fromMac(const std::string string) { return fromId(string) && isMacLen(); }
    /**
     * Check if ID length is a valid MAC address
     * @return true if ID length is valid MAC length
     */
    bool isMacLen() const { return length() == EUI48 || length() == EUI64; }
    /**
     * Convert ID from EUI48 to EUI64 using 0xfffe padding
     * @return true if ID is EUI64 after conversion
     */
    bool eui48ToEui64();
    /**
     * Convert Hex to binary with optional separators
     * @param[in] hex string
     * @return true if hex is proper
     */
    bool fromHex(const std::string hex);
    /**
     * Convert binary to hex string
     * @return hex string
     */
    std::string toHex() const {
        return bufToHex((uint8_t *)m_str.c_str(), length());
    }
    /**
     * Convert binary to hex string
     * @param[in] bin pointer to memory buffer
     * @param[in] length of memory buffer
     * @return hex string
     */
    static std::string bufToHex(const uint8_t *bin, size_t length);
};

#endif /*__BUF_H*/