#ifndef LIBRT_HTTP_MACOS_P_H
#define LIBRT_HTTP_MACOS_P_H

#include "libgearbox_http_interface_p.h"

@class librtCocoaHttpPrivate;
@class NSMutableURLRequest;
@class NSURLSession;

namespace librt
{
    class CocoaHttp
    {
    private:
        using milliseconds_t = librt::http::milliseconds_t;
        using http_header_t = librt::http::header_t;
        using http_header_array_t = librt::http::header_array_t;
        using http_port_t = librt::http::port_t;
        using http_request_t = librt::http::RequestType;
        using http_ssl_error_handling_t = librt::http::SSLErrorHandling;
        using http_status_t = librt::http::Status;
        using http_error_t = librt::http::Error;
        using http_request_result_t = librt::http::RequestResult;

    public:
        explicit CocoaHttp(const std::string &userAgent);
        CocoaHttp(CocoaHttp &&) = default;
        CocoaHttp &operator =(CocoaHttp &&) = default;
        ~CocoaHttp();

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
            Request(NSMutableURLRequest *request);
            Request(Request &&) noexcept(true);
            Request &operator =(Request &&) noexcept(true);
            ~Request() noexcept(true);

        public:
            void setBody(const std::string &data);
            void setHeaders(const http_header_array_t &headers);
            void setHeader(const http_header_t &header);

        public:
            http_request_result_t send();

        private:
            NSMutableURLRequest *request_;
            NSURLSession *session_;
            
        private:
            DISABLE_COPY(Request);
        };
        Request createRequest();

    private:
        std::string hostname_;
        http_port_t port_;
        std::string path_;
        bool authenticationEnabled_;
        struct { std::string username; std::string password; } authentication_;
        bool sslErrorHandlingEnabled_;
        milliseconds_t timeout_;
        
    private:
        librtCocoaHttpPrivate *impl_;
    };
}

#endif // LIBRT_HTTP_MACOS_P_H
