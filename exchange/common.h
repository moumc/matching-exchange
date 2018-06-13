#ifndef __COMMON_H__
#define __COMMON_H__

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <time.h>

//#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
//#include <set>
//#include <unordered_map>
//#include <unordered_set>
//#include <random>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>
//#include <condition_variable>
//#include <functional>

//#include "bitcoin/uint256.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::deque;
using std::map;
//using std::set;
//using std::pair;
using std::make_pair;
using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::atomic;
using std::thread;
using std::mutex;
using std::lock_guard;
using std::unique_lock;
//using std::condition_variable;

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;
typedef lock_guard<mutex> ScopeLock;
typedef unique_lock<mutex> UniqueLock;
//typedef condition_variable Condition;


const int BUY = 1;
const int SELL = 2;
const int BUYCANCEL = 3;
const int SELLCANCEL = 4;

const int RET_OK = 0;
const int RET_ERR = 1;

const string CompareGt = "gt";
const string CompareEq = "eq";
const string CompareLt = "lt";

#endif
