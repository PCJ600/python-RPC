#!/usr/bin/python3
#coding=utf-8

import rpyc

def main():
    c = rpyc.connect('localhost', 60001, config = {'sync_request_timeout':60})
    print('teststr should be 1234, now is:', c.root.test())
    
    c.root.load_so('./deps/libadd.so')
    res = c.root.test_add('./deps/libadd.so', 1, 2)
    print('1 + 2 =', res)
    c.close()

if __name__ == "__main__":
    main()
