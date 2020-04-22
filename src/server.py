#!/usr/bin/python3
#coding=utf-8

import rpyc
import ctypes

class MyService(rpyc.Service):
    def __init__(self):
        self.loaded_so = {}


    def on_connect(self, conn):
        pass
    
    def on_disconnect(self, conn):
        pass

    def exposed_test(self):
        return "1234"

    def exposed_load_so(self, so_path):
        self.loaded_so[so_path] = ctypes.CDLL(so_path, mode=ctypes.DEFAULT_MODE)
    
    
if __name__ == "__main__":
    from rpyc.utils.server import ThreadedServer
    server = ThreadedServer(MyService, port=60001)
    server.start()
