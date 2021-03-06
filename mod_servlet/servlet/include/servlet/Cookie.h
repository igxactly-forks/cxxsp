/*
 * ====================================================================
 *
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 1999-2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution, if
 *    any, must include the following acknowlegement:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowlegement may appear in the software itself,
 *    if and wherever such third-party acknowlegements normally appear.
 *
 * 4. The names "The Jakarta Project", "Tomcat", and "Apache Software
 *    Foundation" must not be used to endorse or promote products derived
 *    from this software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
 *    permission of the Apache Group.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 */

#ifndef COOKIE_H
#define COOKIE_H

#include <ctype.h> //tolower
#include <string>

namespace servlet {

/**
 *
 * Creates a cookie, a small amount of information sent by a servlet to
 * a Web browser, saved by the browser, and later sent back to the server.
 * A cookie's value can uniquely
 * identify a client, so cookies are commonly used for session management.
 *
 * <p>A cookie has a name, a single value, and optional attributes
 * such as a comment, path and domain qualifiers, a maximum age, and a
 * version number. Some Web browsers have bugs in how they handle the
 * optional attributes, so use them sparingly to improve the interoperability
 * of your servlets.
 *
 * <p>The servlet sends cookies to the browser by using the
 * {@link HttpServletResponse#addCookie} method, which adds
 * fields to HTTP response headers to send cookies to the
 * browser, one at a time. The browser is expected to
 * support 20 cookies for each Web server, 300 cookies total, and
 * may limit cookie size to 4 KB each.
 *
 * <p>The browser returns cookies to the servlet by adding
 * fields to HTTP request headers. Cookies can be retrieved
 * from a request by using the {@link HttpServletRequest#getCookies} method.
 * Several cookies might have the same name but different path attributes.
 *
 * <p>Cookies affect the caching of the Web pages that use them.
 * HTTP 1.0 does not cache pages that use cookies created with
 * this class. This class does not support the cache control
 * defined with HTTP 1.1.
 *
 * <p>This class supports both the Version 0 (by Netscape) and Version 1
 * (by RFC 2109) cookie specifications. By default, cookies are
 * created using Version 0 to ensure the best interoperability.
 *
 *
 * @author      Various
 * @version     $Version$
 *
 */
class Cookie {
    //
    // The value of the cookie itself.
    //
    std::string name;         // NAME= ... "$Name" style is reserved
    std::string value;        // value of NAME

    //
    // Attributes encoded in the header's cookie fields.
    //
    std::string comment;     // ;Comment=VALUE ... describes cookie's use
                             // ;Discard ... implied by maxAge < 0
    std::string domain;      // ;Domain=VALUE ... domain that sees cookie
    int maxAge;              // ;Max-Age=VALUE ... cookies auto-expire
    std::string path;        // ;Path=VALUE ... URLs that see the cookie
    bool secure;             // ;Secure ... e.g. use SSL
    int version;             // ;Version=1 ... means RFC 2109++ style
public:



    /**
     * Constructs a cookie with a specified name and value.
     *
     * <p>The name must conform to RFC 2109. That means it can contain
     * only ASCII alphanumeric characters and cannot contain commas,
     * semicolons, or white space or begin with a $ character. The cookie's
     * name cannot be changed after creation.
     *
     * <p>The value can be anything the server chooses to send. Its
     * value is probably of interest only to the server. The cookie's
     * value can be changed after creation with the
     * <code>setValue</code> method.
     *
     * <p>By default, cookies are created according to the Netscape
     * cookie specification. The version can be changed with the
     * <code>setVersion</code> method.
     *
     *
     * @param name                      a <code>String</code> specifying the name of the cookie
     *
     * @param value                     a <code>String</code> specifying the value of the cookie
     *
     * @throws IllegalArgumentException if the cookie name contains illegal characters
     *                                  (for example, a comma, space, or semicolon)
     *                                  or it is one of the tokens reserved for use
     *                                  by the cookie protocol
     * @see #setValue
     * @see #setVersion
     *
     */
    Cookie(const std::string& name, const std::string& value);



    /**
     *
     * Specifies a comment that describes a cookie's purpose.
     * The comment is useful if the browser presents the cookie
     * to the user. Comments
     * are not supported by Netscape Version 0 cookies.
     *
     * @param purpose           a <code>String</code> specifying the comment
     *                          to display to the user
     *
     * @see #getComment
     *
     */
    void  setComment(const std::string& purpose)
        { comment = purpose; }


    /**
     * Returns the comment describing the purpose of this cookie, or
     * <code>null</code> if the cookie has no comment.
     *
     * @return                  a <code>String</code> containing the comment,
     *                          or <code>null</code> if none
     *
     * @see #setComment
     *
     */
    std::string  getComment() const
        { return comment; }



    /**
     *
     * Specifies the domain within which this cookie should be presented.
     *
     * <p>The form of the domain name is specified by RFC 2109. A domain
     * name begins with a dot (<code>.foo.com</code>) and means that
     * the cookie is visible to servers in a specified Domain Name System
     * (DNS) zone (for example, <code>www.foo.com</code>, but not
     * <code>a.b.foo.com</code>). By default, cookies are only returned
     * to the server that sent them.
     *
     *
     * @param pattern           a <code>String</code> containing the domain name
     *                          within which this cookie is visible;
     *                          form is according to RFC 2109
     *
     * @see #getDomain
     *
     */
    void  setDomain(const std::string& pattern) {
        domain.resize(pattern.size());
        std::transform(pattern.begin(), pattern.end(), domain.begin(), tolower); // IE allegedly needs this
    }



    /**
     * Returns the domain name set for this cookie. The form of
     * the domain name is set by RFC 2109.
     *
     * @return                  a <code>String</code> containing the domain name
     *
     * @see #setDomain
     *
     */
    std::string  getDomain() const
        { return domain; }


    /**
     * Sets the maximum age of the cookie in seconds.
     *
     * <p>A positive value indicates that the cookie will expire
     * after that many seconds have passed. Note that the value is
     * the <i>maximum</i> age when the cookie will expire, not the cookie's
     * current age.
     *
     * <p>A negative value means
     * that the cookie is not stored persistently and will be deleted
     * when the Web browser exits. A zero value causes the cookie
     * to be deleted.
     *
     * @param expiry            an integer specifying the maximum age of the
     *                          cookie in seconds; if negative, means
     *                          the cookie is not stored; if zero, deletes
     *                          the cookie
     *
     *
     * @see #getMaxAge
     *
     */
    void  setMaxAge(int expiry)
        { maxAge = expiry; }


    /**
     * Returns the maximum age of the cookie, specified in seconds,
     * By default, <code>-1</code> indicating the cookie will persist
     * until browser shutdown.
     *
     *
     * @return                  an integer specifying the maximum age of the
     *                          cookie in seconds; if negative, means
     *                          the cookie persists until browser shutdown
     *
     *
     * @see #setMaxAge
     *
     */
    int  getMaxAge() const
        { return maxAge; }



    /**
     * Specifies a path for the cookie
     * to which the client should return the cookie.
     *
     * <p>The cookie is visible to all the pages in the directory
     * you specify, and all the pages in that directory's subdirectories.
     * A cookie's path must include the servlet that set the cookie,
     * for example, <i>/catalog</i>, which makes the cookie
     * visible to all directories on the server under <i>/catalog</i>.
     *
     * <p>Consult RFC 2109 (available on the Internet) for more
     * information on setting path names for cookies.
     *
     *
     * @param uri               a <code>String</code> specifying a path
     *
     *
     * @see #getPath
     *
     */
    void  setPath(const std::string& uri)
        { path = uri; }



    /**
     * Returns the path on the server
     * to which the browser returns this cookie. The
     * cookie is visible to all subpaths on the server.
     *
     *
     * @return          a <code>String</code> specifying a path that contains
     *                  a servlet name, for example, <i>/catalog</i>
     *
     * @see #setPath
     *
     */
    std::string  getPath() const
        { return path; }



    /**
     * Indicates to the browser whether the cookie should only be sent
     * using a secure protocol, such as HTTPS or SSL.
     *
     * <p>The default value is <code>false</code>.
     *
     * @param flag      if <code>true</code>, sends the cookie from the browser
     *                  to the server only when using a secure protocol;
     *                  if <code>false</code>, sent on any protocol
     *
     * @see #getSecure
     *
     */
    void  setSecure(bool flag)
        { secure = flag; }


    /**
     * Returns <code>true</code> if the browser is sending cookies
     * only over a secure protocol, or <code>false</code> if the
     * browser can send cookies using any protocol.
     *
     * @return          <code>true</code> if the browser uses a secure protocol;
     *                   otherwise, <code>true</code>
     *
     * @see #setSecure
     *
     */
    bool  getSecure() const
        { return secure; }



    /**
     * Returns the name of the cookie. The name cannot be changed after
     * creation.
     *
     * @return          a <code>String</code> specifying the cookie's name
     *
     */
    std::string  getName() const
        { return name; }



    /**
     *
     * Assigns a new value to a cookie after the cookie is created.
     * If you use a binary value, you may want to use BASE64 encoding.
     *
     * <p>With Version 0 cookies, values should not contain white
     * space, brackets, parentheses, equals signs, commas,
     * double quotes, slashes, question marks, at signs, colons,
     * and semicolons. Empty values may not behave the same way
     * on all browsers.
     *
     * @param newValue          a <code>String</code> specifying the new value
     *
     *
     * @see #getValue
     * @see Cookie
     *
     */
    void  setValue(const std::string& newValue)
        { value = newValue; }



    /**
     * Returns the value of the cookie.
     *
     * @return                  a <code>String</code> containing the cookie's
     *                          present value
     *
     * @see #setValue
     * @see Cookie
     *
     */
    std::string  getValue() const
        { return value; }


    /**
     * Returns the version of the protocol this cookie complies
     * with. Version 1 complies with RFC 2109,
     * and version 0 complies with the original
     * cookie specification drafted by Netscape. Cookies provided
     * by a browser use and identify the browser's cookie version.
     *
     *
     * @return                  0 if the cookie complies with the
     *                          original Netscape specification; 1
     *                          if the cookie complies with RFC 2109
     *
     * @see #setVersion
     *
     */
    int  getVersion() const
        { return version; }




    /**
     * Sets the version of the cookie protocol this cookie complies
     * with. Version 0 complies with the original Netscape cookie
     * specification. Version 1 complies with RFC 2109.
     *
     * <p>Since RFC 2109 is still somewhat new, consider
     * version 1 as experimental; do not use it yet on production sites.
     *
     *
     * @param v                 0 if the cookie should comply with
     *                          the original Netscape specification;
     *                          1 if the cookie should comply with RFC 2109
     *
     * @see #getVersion
     *
     */
    void  setVersion(int v)
        { version = v; }

private:


    /*
     * Tests a string and returns true if the string counts as a
     * reserved token in the Java language.
     *
     * @param value             the <code>String</code> to be tested
     *
     * @return                  <code>true</code> if the <code>String</code> is
     *                          a reserved token; <code>false</code>
     *                          if it is not
     */
    bool  isValidName(const std::string& value) const;
};

}//namespace

#endif/*COOKIE_H*/
