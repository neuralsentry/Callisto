bool qemu_net_queue_flush(NetQueue *queue)

{

    while (!QTAILQ_EMPTY(&queue->packets)) {

        NetPacket *packet;

        int ret;



        packet = QTAILQ_FIRST(&queue->packets);

        QTAILQ_REMOVE(&queue->packets, packet, entry);

        queue->nq_count--;



        ret = qemu_net_queue_deliver(queue,

                                     packet->sender,

                                     packet->flags,

                                     packet->data,

                                     packet->size);

        if (ret == 0) {


            QTAILQ_INSERT_HEAD(&queue->packets, packet, entry);

            return false;

        }



        if (packet->sent_cb) {

            packet->sent_cb(packet->sender, ret);

        }



        g_free(packet);

    }

    return true;

}