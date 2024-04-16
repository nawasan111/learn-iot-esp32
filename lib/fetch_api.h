#include <WiFi.h>

enum Method { GET, POST, PUT, DELETE };

String method_parser(Method m) {
  if (m == Method::GET) return String("GET");
  if (m == Method::POST) return String("POST");
  if (m == Method::PUT) return String("POST");
  if (m == Method::DELETE) return String("DELETE");
}

class URL {
 public:
  String domain;
  String path;
  URL(String domain, String path) {
    this->domain = domain;
    this->path = path;
  }
};

String header_parse(String h[], int len) {
  String head = "";
  for (int i = 0; i < len; i++) {
    head += h[i] + '\n';
  }
  return head;
}

class Fetch {
 private:
  WiFiClient client;
  String host = "";
  int port = 80;

 public:
  void get(String url, String body = "", String header = "") {
    send(Method::GET, url, body, header);
  }
  void post(String url, String body = "", String header = "") {
    send(Method::POST, url, body, header);
  }
  void put(String url, String body = "", String header = "") {
    send(Method::PUT, url, body, header);
  }
  void delete(String url, String body = "", String header = "") {
    send(Method::DELETE, url, body, header);
  }

  void send(Method m, String url, String body = "", String header = "") {
    String payload = "";
    URL urlp = url_parser(url);

    if (host.length() > 0) {
      urlp.domain = host;
    }
    if (!client.connect(urlp.domain, port)) {
      return;
    }
    payload += method_parser(m) + " " + urlp.path + " HTTP/1.1\n";
    payload += "Host: " + urlp.domain + "\n";
    payload += "Connection: close\n";
    payload += "Content-Type: application/x-www-form-urlencoded\n";
    payload += header;
    payload += "Content-Length: " + String(body.length()) + "\n\n";
    payload += body;
    client.print(payload);
  }
  URL url_parser(String url) {
    String domain = "";
    String path = "";
    bool is_domain = true;
    int url_len = url.length();
    for (int i = 0; i < url_len; i++) {
      if (is_domain && url[i] == '/') {
        is_domain = false;
      }
      if (is_domain) {
        domain += url[i];
      } else {
        path += url[i];
      }
    }
    return URL(domain, path);
  }
};