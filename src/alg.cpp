// Copyright 2021 NNTU-CS
#include <algorithm>
#include <chrono>
#include <thread>

int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] + arr[j] == value) {
                count++;
            }
        }
    }
    return count;
}

int countPairs2(int *arr, int len, int value) {
    int count = 0;
  for (int i = 0; i < len; i++) {
    if (arr[i] + arr[len - 1] < value) {
        continue;
    }
    if (arr[i] + arr[i + 1] > value) {
        break;
    }
    for (int j = i + 1; j < len; j++) {
        if (arr[i] + arr[j] > value) {
            break;
        }
        if (arr[i] + arr[j] == value) {
            count++;
        }
    }
  }
  return count;
}
int binarySearch(int *arr, int left, int right, int target) {
  int first = -1, last = -1;
  int low = left, high = right - 1;
  while (low <= high) {
      int mid = low + (high - low) / 2;
      if (arr[mid] == target) {
          first = mid;
          high = mid - 1;
      } else if (arr[mid] < target) {
          low = mid + 1;
      } else {
          high = mid - 1;
      }
  }
  if (first == -1) return 0;
  low = first, high = right - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) {
        last = mid;
        low = mid + 1;
    } else if (arr[mid] < target) {
        low = mid + 1;
    } else {
        high = mid - 1;
    }
  }
  return last - first + 1;
}

int countPairs3(int *arr, int len, int value) {
    int count = 0;
  for (int i = 0; i < len; i++) {
      int target = value - arr[i];
      int targetCount = binarySearch(arr, i + 1, len, target);
      count += targetCount;
  }
  return count;
}
