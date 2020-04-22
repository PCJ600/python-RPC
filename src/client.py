#!/usr/bin/python3
#coding=utf-8

import rpyc


def main():
    c = rpyc.connect('localhost', 60001, config = {'sync_request_timeout':60})
    print(c.root.test())
    c.close()

if __name__ == "__main__":
    main()
