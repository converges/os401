import threading
import time

sem = threading.Semaphore(5)

def run(n):

    for x in range(3):
        sem.acquire()
        print(f"Thread {n}:{x} running")
        time.sleep(1)
        sem.release()


if __name__ == "__main__":
    threads = []

    for i in range(10):
        threads.append(threading.Thread(target=run, args=(i,)))

    for th in threads:
        th.start()

    for th in threads:
        th.join()

    print("Finished")


