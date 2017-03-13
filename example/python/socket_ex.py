#!/usr/bin/python

import socket

IP_VERSIONS = {
    4: socket.AF_INET,
    6: socket.AF_INET6
}

def parse_endpoint(endpoint):
    host, port = endpoint.split(':')
    return (host, int(port))

def pack_endpoint(host, port):
    return '{}:{}'.format(host, port)

class Socket(object):
    def __init__(self, socket):
        self.socket = socket

    def __enter__(self, *a): return self
    def __exit__(self, *a): self.close()

    # Common
    def close(self): self.socket.close()

    def bind(self, endpoint=None):
        if endpoint: self.socket.bind(parse_endpoint(endpoint))
        return pack_endpoint(*self.socket.getsockname())

    # Options
    def set_timeout(self, value): self.socket.settimeout(value)

    def set_option(self, option, value):
        self.socket.setsockopt(socket.SOL_SOCKET, option, value)

class TcpSocket(Socket):
    def __init__(self, ipVersion = 4, fd = None, remote_address = None):
        if not fd: fd = socket.socket(IP_VERSIONS[ipVersion], socket.SOCK_STREAM)
        super(TcpSocket, self).__init__(fd)
        self.remote_address = remote_address

    # Server
    def listen(self, queue=128):
        return self.socket.listen(queue)

    def accept(self):
        socket, address = self.socket.accept()
        return TcpSocket(fd = socket, remote_address = pack_endpoint(*address))

    # Client
    def connect(self, endpoint):
        self.remote_address = endpoint
        return self.socket.connect(parse_endpoint(endpoint))

    # Stream
    def send(self, data): return self.socket.send(data)
    def recv(self, size = 1024): return self.socket.recv(size)

    # Options
    def setKeepAlive(self, value=True, idle=10, interval=10, count=3):
        if value:
            self.set_option(socket.SO_KEEPALIVE, 1)
            self.set_tcp_option(socket.TCP_KEEPIDLE, idle)
            self.set_tcp_option(socket.TCP_KEEPINTVL, interval)
            self.set_tcp_option(socket.TCP_KEEPCNT, count)
        else:
            self._set_option(socket.SO_KEEPALIVE, 0)

    def set_tcp_option(self, option, value):
        self.socket.setsockopt(socket.SOL_TCP, option, value)

def main():
    import sys
    from datetime import datetime
    def log(message, *args):
        sys.stdout.write('{} {}\n'.format(datetime.now(), message.format(*args)))

    with TcpSocket() as server:
        address = server.bind('0.0.0.0:0')
        server.listen()
        log('Server address: {}', address)

        def serverRun():
            client = server.accept()
            client.set_timeout(100)
            log('Server accepted: {}', client.remote_address)
            while True:
                data = client.recv()
                log('Server got: {}', data or 'END_OF_TREAM')
                if not data: return
                client.send(data)
                log('Server sent data copy')

        from threading import Thread
        thread = Thread(target=serverRun)
        thread.start()

        with TcpSocket() as client:
            client.setKeepAlive(idle=5, interval=5, count=1)
            client.connect(address)

            log('Client connected')
            client.send('Hello World!')
            log('Client sent some data')
            log('Client got: {}', client.recv() or 'END_OF_TREAM')

        thread.join()
        log('Done')

if __name__ == '__main__':
    main()
