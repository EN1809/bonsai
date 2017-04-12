#ifndef UNIX_PLATFORM_CPP
#define UNIX_PLATFORM_CPP

#include <unix_platform.h>
#include <platform.h>

inline unsigned int
AtomicCompareExchange( volatile unsigned int *Source, unsigned int Exchange, unsigned int Comparator )
{
  unsigned int Result = __sync_val_compare_and_swap ( Source, Comparator, Exchange);
  return Result;
}

inline void
ThreadSleep( semaphore Semaphore )
{
  /* WaitForSingleObject( Semaphore, INFINITE ); */
  return;
}

inline void
WakeThread( semaphore Semaphore )
{
  /* ReleaseSemaphore( Semaphore, 1, 0 ); */
  return;
}

semaphore
CreateSemaphore( int ThreadCount )
{
  /* semaphore Result = CreateSemaphore( 0, 0, ThreadCount, 0); */
  return 0;
}

int
GetLogicalCoreCount()
{
  int Result = sysconf(_SC_NPROCESSORS_ONLN);
  return Result;
}

thread_id
CreateThread( void* (*ThreadMain)(void*), thread_startup_params *Params)
{
  pthread_t Thread;

  pthread_attr_t Attribs;
  pthread_attr_init(&Attribs);

  Params->Self.ID = pthread_create(&Thread, &Attribs, ThreadMain, Params);

  return Params->Self.ID;
}

#define CompleteAllWrites  asm volatile("" ::: "memory"); _mm_sfence()

__inline__ unsigned long long
GetCycleCount()
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));

  unsigned long long Result = ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );

  return Result;
}

#endif
