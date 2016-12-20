#include "HttpWrapper.h"
#include "HTTP\http.h"

int HttpWrapper::HttpRequest(string url) {
	Net::HttpClient client;
	client.get_content(url);
	return 0;
}