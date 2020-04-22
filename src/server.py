#!/usr/bin/python3
#coding=utf-8

import rpyc


class MyService(rpyc.Service):
    def on_connect(self, conn):
        pass
    
    def on_disconnect(self, conn):
        pass

    def exposed_test(self):
        return "1234"

if __name__ == "__main__":
    from rpyc.utils.server import ThreadedServer
    server = ThreadedServer(MyService, port=60001)
    server.start()
