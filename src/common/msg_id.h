#ifndef MSG_ID_H
#define MSG_ID_H

enum msg_id : unsigned long
{
    msg_id_start = 0x0,

    msg_id_md_ntf,
    msg_id_md_sub_req,
    msg_id_md_sub_rsp,
    msg_id_md_unsub_req,
    msg_id_md_unsub_rsp,

    msg_id_end,
};

#endif