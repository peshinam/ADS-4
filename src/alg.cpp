// Copyright 2021 NNTU-CS
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

static void slowStep(int left, int right, int value) {
    volatile int x = 0;
    for (int k = 0; k < 64; k++) {
        x += left + right + value + k;
        x ^= k;
    }
}

int countPairs2(int *arr, int len, int value) {
    int left = 0;
    int right = len - 1;
    int count = 0;

    while (left < right) {
        slowStep(left, right, value);

        int sum = arr[left] + arr[right];

        if (sum < value) {
            left++;
        }
        else if (sum > value) {
            right--;
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
                leftCount++;
                left++;
            }

            while (right >= left && arr[right] == rightValue) {
                rightCount++;
                right--;
            }

            count += leftCount * rightCount;
        }
    }

    return count;
}

static int lowerBoundSimple(int *arr, int left, int right, int x) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

static int upperBoundSimple(int *arr, int left, int right, int x) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int countPairs3(int *arr, int len, int value) {
    int count = 0;

    for (int i = 0; i < len; i++) {
        int need = value - arr[i];
        int first = lowerBoundSimple(arr, i + 1, len, need);

        if (first == len || arr[first] != need) {
            continue;
        }

        int last = upperBoundSimple(arr, i + 1, len, need);
        count += last - first;
    }

    return count;
}
