#ifndef LAIYANG_H_
#define LAIYANG_H_

/* processes record their normal (i.e. char[]) messages */

typedef struct NormalSentMessage {
	int destination;
	int arrival_number;
} NormalSentMessage;


/* processes record the normal messages they receive */

typedef struct NormalReceivedMessage {
	int source;
	int arrival_number;
	char content[100];
} NormalReceivedMessage;


/* used for passing Control-type content (i.e. info about send messages) between processes */

typedef struct Control {
	int total_messages_on_channel;
	int messages_ids[10];
} Control;


/* processes record the control messages they receive */

typedef struct ControlReceivedMessage {
	int source;
	Control control_message;
	int all_messages_received;
} ControlReceivedMessage;


/* the local (partial) snapshot each process builds;
 * also used for passing Snapshot-type content;
 * the initiating process also has a list of such Snapshots */

typedef struct Snapshot {
	int process_rank;
	int x;
	int total_sent_messages;
	int total_received_messages;
	NormalSentMessage sent_messages[100];
	NormalReceivedMessage received_messages[100];
} Snapshot;


/* the general message type through which processes communicate;
 * only one of the content types (i.e. normal, control, snapshot) should be filled in / accessed at a time */

typedef struct Message {
	int type;
	int tag;
	int arrival_number;

	char normal_content[100];
	Control control_content;
	Snapshot snapshot_content;
} Message;


void print_snapshots(int rank, int total_snapshots, Snapshot snapshots[100], int total_messages_sent_in_network, int total_messages_received_in_network);

#endif /* LAIYANG_H_ */
