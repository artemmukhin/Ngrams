//
// Created by opot on 07.03.17.
//

#include "TextProcessor.h"


TextProcessor::TextProcessor(HashTable *tree) {
    for(int i = 0; i < PROCESS_THREAD_NUM; i++){
        pthread_create(&threads[i], NULL, routine, (void*)&data[i]);
        pthread_mutex_init(&data[i].mutex, NULL);
        data[i].start = &start;
        data[i].tree = tree;
    }
    pthread_cond_init(&start, NULL);
}

void TextProcessor::process(const char *str, int length, int num) {

    for(int i = 0; i < PROCESS_THREAD_NUM; i++){
        data[i].str = &str[length / PROCESS_THREAD_NUM * i];
        data[i].full_length = length - length / PROCESS_THREAD_NUM * i;
        data[i].part_length = length / PROCESS_THREAD_NUM * i;
        data[i].num = num;

        pthread_mutex_lock(&data[i].mutex);
    }
    pthread_cond_broadcast(&start);

    //TODO result process

    for(int i = 0; i < PROCESS_THREAD_NUM; i++)
        pthread_mutex_unlock(&data[i].mutex);
}

FoundSet* searchInText(HashTable *tree, const char *str, int part_length, int full_length, int num)
{
    uint64_t *hashes = new uint64_t[HashEngine::MAX_LEN + 1];
    HashEngine::hashesOfPrefixes(str, length, hashes);

    string currWord = "";
    string *result = new string();
    const SuffixList *suffixes;
    size_t i = 0;
    FoundSet foundSuffixes(HashEngine::FOUND_SET_SIZE);

    while (i <= length) {
        if (str[i] == ' ' || i == length) {
            suffixes = this->suffixesOf({currWord.c_str(), currWord.length(),
                                         HashEngine::hashOfString(currWord.c_str(), currWord.length())
                                        });

            if (suffixes) {
                SuffixNode *suffixNode = suffixes->getHead();
                while (suffixNode) {
                    uint64_t textHash = hashes[i + suffixNode->suffix.length] -
                                        hashes[i] * HashEngine::POWERS[suffixNode->suffix.length];

                    if (!suffixNode->isFound) {
                        HString textSuffix {&(str[i]), suffixNode->suffix.length, textHash};
                        if (HashEngine::isEqual(suffixNode->suffix, textSuffix)) {
                            if (i + suffixNode->suffix.length == length || str[i + suffixNode->suffix.length] == ' ') {
                                suffixNode->isFound = true;
                                foundSuffixes.add(suffixNode);
                                result->append(currWord);
                                result->append(suffixNode->suffix.str);
                                result->append("|");
                            }
                        }
                    }
                    suffixNode = suffixNode->next;
                }
            }
            currWord = "";
            i++;
        }
        currWord += str[i++];
    }

    uint64_t s = 0;
    while (s < foundSuffixes.current) {
        foundSuffixes.set[s]->isFound = false;
        s++;
    }

    if (!result->empty())
        result->pop_back();
    else
        result = new string("-1");

    return result;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void* TextProcessor::routine(void *data) {
    ThreadData *tdata = (ThreadData*) data;
    while(true) {
        pthread_mutex_lock(&tdata->mutex);
        pthread_cond_wait(tdata->start, &tdata->mutex);

        pthread_mutex_unlock(&tdata->mutex);
    }
}
#pragma clang diagnostic pop