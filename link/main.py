import tornado.httpserver
import tornado.ioloop
import tornado.web
import tornado.websocket
import base64


class WebSocketHandler(tornado.websocket.WebSocketHandler):

    def initialize(self):
        with open("../server/index.js", "rb") as imageFile:
            self.str = base64.b64encode(imageFile.read())

    def open(self):
        print('new connection')
        self.write_message(self.str)

    def on_message(self, message):
        print(message)

    def on_close(self):
        print('connection closed')
  
if __name__ == '__main__':
    application = tornado.web.Application([
        (r'/ws', WebSocketHandler),
    ])
    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(8888)
    tornado.ioloop.IOLoop.instance().start()