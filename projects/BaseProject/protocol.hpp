#ifndef PROTOCOL_HPP_INCLUDED
#define PROTOCOL_HPP_INCLUDED

namespace protocol
{
    const char GET_HOST_PID='@';
    const char NEW_CLIENT_REQ='#';
    const char MSG_CONFIRMED='$';
    const char MSG_FAILED='!';
    int BUF_SIZE=512;
}

#endif // PROTOCOL_HPP_INCLUDED
