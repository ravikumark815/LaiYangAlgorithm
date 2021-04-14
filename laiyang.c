#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"
#include "laiyang.h"

void print_snapshots(int rank, int total_snapshots, Snapshot snapshots[100], int total_messages_sent_in_network, int total_messages_received_in_network) {

	int i, j;
	char output[2000000], temp_output[100000];

	sprintf(output, "[SNAPSHOT - process %d] I have a total of %d local snapshots. \n"
					"[SNAPSHOT - process %d] In this network, there were a total of %d messages sent and %d messages received. \n"
					"[SNAPSHOT - process %d] The global snapshot: \n",
					rank, total_snapshots, rank, total_messages_sent_in_network, total_messages_received_in_network, rank);

	for (i = 0; i < total_snapshots; i++) {
		sprintf(temp_output, "\n[SNAPSHOT - process %d] Snapshot %d: \n", rank, i);

		strcat(output, temp_output);
		memset(temp_output, 0, sizeof temp_output);

		sprintf(temp_output, "[SNAPSHOT - process %d] process_rank (source): %d\n", rank, snapshots[i].process_rank);

		strcat(output, temp_output);
		memset(temp_output, 0, sizeof temp_output);

		sprintf(temp_output, "[SNAPSHOT - process %d] variable x: %d \n", rank, snapshots[i].x);

		strcat(output, temp_output);
		memset(temp_output, 0, sizeof temp_output);

		sprintf(temp_output, "[SNAPSHOT - process %d] total messages sent by this process: %d \n", rank, snapshots[i].total_sent_messages);

		strcat(output, temp_output);
		memset(temp_output, 0, sizeof temp_output);

		sprintf(temp_output, "[SNAPSHOT - process %d] total messages received by this process: %d \n", rank, snapshots[i].total_received_messages);

		strcat(output, temp_output);
		memset(temp_output, 0, sizeof temp_output);

		sprintf(temp_output, "[SNAPSHOT - process %d] Received messages: \n", rank);

		strcat(output, temp_output);
		memset(temp_output, 0, sizeof temp_output);

		for (j = 0; j < snapshots[i].total_received_messages; j++) {

			sprintf(temp_output, "[SNAPSHOT - process %d] Message source: %d; message arrival number: %d; message content: %s \n",
					rank, snapshots[i].received_messages[j].source, snapshots[i].received_messages[j].arrival_number, snapshots[i].received_messages[j].content);

			strcat(output, temp_output);
			memset(temp_output, 0, sizeof temp_output);
		}
	}

	printf(output);
}
