// Copyright 2021 NNTU-CS
int countPairs1(int *arr, int len, int value) {
  int count = 0;

    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value)
                ++count;
        }
    }

    return count;
}
int countPairs2(int *arr, int len, int value) {
  int left = 0;
    int right = len - 1;
    int count = 0;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum < value) {
            ++left;
        }
        else if (sum > value) {
            --right;
        }
        else {
            if (arr[left] == arr[right]) {
                int k = right - left + 1;
                count += k * (k - 1) / 2;
                break;
            }

            int leftValue = arr[left];
            int rightValue = arr[right];
            int leftCount = 0;
            int rightCount = 0;

            while (left <= right && arr[left] == leftValue) {
                ++left;
                ++leftCount;
            }

            while (right >= left && arr[right] == rightValue) {
                --right;
                ++rightCount;
            }

            count += leftCount * rightCount;
        }
    }

    return count;
}
static int lowerBoundIndex(int *arr, int left, int right, int target) {
    int l = left;
    int r = right;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

static int upperBoundIndex(int *arr, int left, int right, int target) {
    int l = left;
    int r = right;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] <= target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
int countPairs3(int *arr, int len, int value) {
  int count = 0;

    for (int i = 0; i < len; ++i) {
        int need = value - arr[i];
        int first = lowerBoundIndex(arr, i + 1, len, need);

        if (first == len || arr[first] != need)
            continue;

        int last = upperBoundIndex(arr, i + 1, len, need);
        count += last - first;
    }

    return count;
}
