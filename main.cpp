#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <cstdint>
#include "NgramTree.h"
#include "thpool.h"

#define NUM_THREADS 4

using namespace std;

int main()
{
    int rc;
    int i;
    NgramTree ngrams;

    threadpool thpool = thpool_init(NUM_THREADS);

    string query = "";
    getline(cin, query);
    do {
        ngrams.add(query);
        getline(cin, query);
    } while (query != "S");

    ngrams.print();
    cout << endl;

    query = "";
    getline(cin, query);
    do {
        switch (query[0]) {
            case 'Q':
                query.erase(0, 2);
                cout << ngrams.searchInText(query) << endl;
                break;

            case 'A':
                query.erase(0, 2);
                ngrams.add(query);
                break;

            case 'D':
                query.erase(0, 2);
                string prefix = "";
                string suffix = "";
                size_t j;
                for (j = 0; j < query.length() && query[j] != ' '; j++);
                prefix = query.substr(0, j);
                suffix = query.substr(j, query.length());
                ngrams.remove(prefix, suffix);
                break;
        }

        cout << endl;
        ngrams.print();
        cout << endl;

        getline(cin, query);
    } while (query != "F");


    //thpool_add_work(thpool, (void*)task1, NULL);

    /*

    for (i = 0; i < NUM_THREADS; i++) {
        cout << "main() : creating thread, " << i << endl;
        rc = pthread_create(&threads[i], &attr, wait, (void *)i);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }

    // free attribute and wait for the other threads
    pthread_attr_destroy(&attr);

    for (i = 0; i < NUM_THREADS; i++) {
        cout << "Waiting for thread " << i << endl;
        rc = pthread_join(threads[i], &status);

        if (rc){
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }

        cout << "Main: completed thread id: " << i ;
        cout << "  exiting with status: " << status << endl;
    }

    cout << "Main: program exiting." << endl;
    pthread_exit(NULL);
    */
    return 0;
}
