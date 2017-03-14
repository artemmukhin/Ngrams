#include "TextProcessor.h"

TextProcessor::TextProcessor(HashTable *tree)
{
    pthread_cond_init(&startCond, NULL);
    pthread_cond_init(&finishCond, NULL);
    for (int i = 0; i < PROCESS_THREAD_NUM; i++) {
        pthread_mutex_init(&data[i].mutexSleep, NULL);
        pthread_mutex_init(&data[i].mutexWork, NULL);
        data[i].wake_up = &startCond;
        data[i].sleep = &finishCond;
        data[i].isStarted = false;
        data[i].tree = tree;
        data[i].hashes = &hashes;
        pthread_create(&threads[i], NULL, routine, (void *) &data[i]);
    }
}

void TextProcessor::process(const char *str, int length, int num)
{
    for (int i = 0; i < PROCESS_THREAD_NUM; i++) {
        data[i].str = str;
        // data[i].start = length - (length / PROCESS_THREAD_NUM) * i;
        // data[i].end = (length / PROCESS_THREAD_NUM) * i;
        data[i].start = (length / PROCESS_THREAD_NUM) * i;
        data[i].end = (length / PROCESS_THREAD_NUM) * (i + 1) - 1;
        if (data[i].end > length)
            data[i].end = length;
        data[i].length = length;
        data[i].num = num;

        data[i].isStarted = true;

        // is it necessary?
        pthread_mutex_lock(&data[i].mutexSleep);
    }

    hashes = new uint64_t[HashEngine::MAX_LEN + 1];
    HashEngine::hashesOfPrefixes(str, length, hashes);

    pthread_cond_broadcast(&startCond);
    for (int i = 0; i < PROCESS_THREAD_NUM; i++) {
        pthread_mutex_unlock(&data[i].mutexSleep);
    }

    string result = "";

    // wait for all threads
    for (int i = 0; i < PROCESS_THREAD_NUM; i++) {
        pthread_mutex_lock(&data[i].mutexSleep);
        while (data[i].isStarted)
            pthread_cond_wait(&finishCond, &(data[i].mutexSleep));
        pthread_mutex_unlock(&data[i].mutexSleep);
    }

    for (int i = 0; i < PROCESS_THREAD_NUM; i++) {
        pthread_mutex_lock(&data[i].mutexSleep);
        //puts("waiting for thread");
        /*
        while (data[i].isStarted)
            pthread_cond_wait(&finishCond, &(data[i].mutex));
        */
        //puts("finish waiting");
        uint64_t s = 0;
        while (s < data[i].result->current) {
            if (data[i].result->set[s].node->isFound != -1) {
                data[i].result->set[s].node->isFound = -1;
                result += string(data[i].result->set[s].prefix) + string(data[i].result->set[s].node->suffix.str) + "|";
            }
            s++;
        }

        pthread_mutex_unlock(&data[i].mutexSleep);
    }

    if (result == "")
        result = "-1";
    else
        result.pop_back();

    puts(result.c_str());
    std::fflush(stdout);
}

void searchInText(ThreadData *data)
{
    string *currWord = new string("");
    const SuffixList *suffixes;
    size_t i = data->start;
    data->result = new FoundSet(HashEngine::FOUND_SET_SIZE);

    if (i > 0) {
        if (data->str[i - 1] != ' ') {
            while (i <= data->end && data->str[i] != ' ')
                i++;
            i++;
        }
    }

    bool isContinue = true;
    while (i <= data->length && isContinue) {
        if (data->str[i] == ' ' || i == data->length) {
            if (i >= data->end) isContinue = false;

            suffixes = data->tree->suffixesOf({currWord->c_str(), currWord->length(),
                                               HashEngine::hashOfString(currWord->c_str(), currWord->length())
                                              });

            if (suffixes) {
                SuffixNode *suffixNode = suffixes->getHead();
                while (suffixNode) {
                    uint64_t textHash = (*(data->hashes))[i + suffixNode->suffix.length] -
                        (*(data->hashes))[i] * HashEngine::POWERS[suffixNode->suffix.length];

                    if (suffixNode->isFound == -1 || suffixNode->isFound > data->num) {
                        HString textSuffix{&(data->str[i]), suffixNode->suffix.length, textHash};
                        if (HashEngine::isEqual(suffixNode->suffix, textSuffix)) {
                            if (i + suffixNode->suffix.length == data->length ||
                                data->str[i + suffixNode->suffix.length] == ' ') {
                                int lastChangeType = suffixNode->lastChangeBefore(data->num);
                                if (lastChangeType == 1) { // 1 for add
                                    suffixNode->isFound = true;
                                    data->result->add(suffixNode, currWord->c_str());
                                }
                            }
                        }
                    }
                    suffixNode = suffixNode->next;
                }
            }
            currWord = new string("");
            i++;
        }
        *currWord += data->str[i++];
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void *TextProcessor::routine(void *data)
{
    ThreadData *tdata = (ThreadData *) data;
    while (true) {
        //puts("routine");

        pthread_mutex_lock(&tdata->mutexWork);
        while (!tdata->isStarted) {
            tdata->isStarted = false;
            pthread_cond_wait(tdata->wake_up, &tdata->mutexWork);
        }
        pthread_mutex_unlock(&tdata->mutexWork);

        pthread_mutex_lock(&tdata->mutexSleep);
        searchInText(tdata);
        tdata->isStarted = false;
        pthread_cond_signal(tdata->sleep);
        //puts("signal for finish");
        pthread_mutex_unlock(&tdata->mutexSleep);
    }
}
#pragma clang diagnostic pop