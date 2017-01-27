#ifndef LIBGEARBOX_HTTP_WIN_P_H
#define LIBGEARBOX_HTTP_WIN_P_H

#include <windows.h>
#include <wininet.h>

#include "libgearbox_global.h"

#include "libgearbox_http_interface_p.h"

namespace gearbox
{
    class WinHttp
    {
    private:
        using milliseconds_t = gearbox::http::milliseconds_t;
        using http_header_t = gearbox::http::header_t;
        using http_header_array_t = gearbox::http::header_array_t;
        using http_port_t = gearbox::http::port_t;
        using http_request_t = gearbox::http::RequestType;
        using http_ssl_error_handling_t = gearbox::http::SSLErrorHandling;
        using http_status_t = gearbox::http::Status;
        using http_error_t = gearbox::http::Error;
        using http_request_result_t = gearbox::http::RequestResult;

    public:
        explicit WinHttp(const std::string &userAgent);
        WinHttp(WinHttp &&other) noexcept(true);
        WinHttp &operator =(WinHttp &&) noexcept(true) = default;
        ~WinHttp();

    public:
        const std::string &host() const;
        void setHost(const std::string &hostname);
        void setHost(std::string &&hostname);

        http_port_t port() const;
        void setPort(http_port_t port);

        const std::string &path() const;
        void setPath(const std::string &path);
        void setPath(std::string &&path);

        bool authenticationRequired() const;
        void enableAuthentication();
        void disableAuthentication();
        const std::string &username() const;
        void setUsername(const std::string &username);
        void setUsername(std::string &&username);

        const std::string &password() const;
        void setPassword(const std::string &password);
        void setPassword(std::string &&password);

        void setSSLErrorHandling(http_ssl_error_handling_t value);

        const milliseconds_t &timeout() const;
        void setTimeout(milliseconds_t value);

    public:
        class Request
        {
        public:
            Request(HINTERNET session,
                    const std::string &path,
                    DWORD connectionFlags,
                    DWORD_PTR &requestId);
            Request(const Request &);             /* Visual Studio thinks it needs this */
            Request &operator =(const Request &); /* Visual Studio thinks it needs this */
            Request(Request &&) noexcept(true) = default;
            Request &operator =(Request &&) noexcept(true) = default;
            ~Request();

        public:
            void setBody(const std::string &data);
            void setHeaders(const http_header_array_t &headers);
            void setHeader(const http_header_t &header);

        public:
            http_request_result_t send();

        private:
            HINTERNET session_;
            const std::string &path_;
            http_request_t requestType_;
            DWORD connectionFlags_;
            DWORD_PTR &requestId_;
            http_header_array_t headers_;
            char *data_;
            DWORD dataSize_;
        };
        Request createRequest();

    private:
        void closeSession();

    private:
        std::string hostname_;
        http_port_t port_;
        std::string path_;
        bool authenticationEnabled_;
        struct { std::string username; std::string password; } authentication_;
        bool sslErrorHandlingEnabled_;
        milliseconds_t timeout_;

    private:
        HINTERNET connection_;
        HINTERNET session_;
        DWORD_PTR requestId_;

    private:
        int connectionFlags_;

    private:
        DISABLE_COPY(WinHttp)
    };
}

#endif // LIBGEARBOX_HTTP_WIN_P_H 
