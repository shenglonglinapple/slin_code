#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oci.h>

static text *username = (text *) "STUDENT";
static text *password = (text *) "LEARN";

/* Define SQL statements to be used in the program. */

static text *course_count = (text *)"SELECT COUNT(*) FROM COURSE";
static text *course_ten = (text *)"SELECT course_no, description, cost FROM course WHERE course_no = 10";
static text *course_low = (text *)"SELECT course_no, description, cost FROM course WHERE course_no < 100";

static OCIEnv *envhp;   // The Env handle is the most basic for Oracle
static OCIError *errhp; // And we use the error handle to retrieve any err info

/* Function prototypes for locally defined functions but with comments */

static void checkerr(/*_ OCIError *errhp, sword status _*/);
static void cleanup(/*_ void _*/);
static void myfflush(/*_ void _*/);
int main(/*_ int argc, char *argv[] _*/);

static sword status;

int main(argc, argv)
int argc;
char *argv[];
{
  sword    ccount;
  sword    cno;
  sword    ccost;
  sb1      descr_buf[51];

  OCISession *authp = (OCISession *) 0;
  OCIServer *srvhp;
  OCISvcCtx *svchp;
  OCIStmt   *stmthp;
  OCIDefine *defnp = (OCIDefine *) 0;
  OCIDefine *defnp1 = (OCIDefine *) 0;
  OCIDefine *defnp2 = (OCIDefine *) 0;
  OCIDefine *defnp3 = (OCIDefine *) 0;

  (void) OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,
                       (dvoid * (*)(dvoid *, size_t)) 0,
                       (dvoid * (*)(dvoid *, dvoid *, size_t))0,
                       (void (*)(dvoid *, dvoid *)) 0 );

  (void) OCIEnvInit( (OCIEnv **) &envhp, OCI_DEFAULT, (size_t) 0,
                     (dvoid **) 0 );

  (void) OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, OCI_HTYPE_ERROR,
                   (size_t) 0, (dvoid **) 0);

  /* server contexts */
  (void) OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, OCI_HTYPE_SERVER,
                   (size_t) 0, (dvoid **) 0);

  (void) OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, OCI_HTYPE_SVCCTX,
                   (size_t) 0, (dvoid **) 0);

  (void) OCIServerAttach( srvhp, errhp, (text *)"", strlen(""), 0);

  /* set attribute server context in the service context */
  (void) OCIAttrSet( (dvoid *) svchp, OCI_HTYPE_SVCCTX, (dvoid *)srvhp,
                     (ub4) 0, OCI_ATTR_SERVER, (OCIError *) errhp);

  (void) OCIHandleAlloc((dvoid *) envhp, (dvoid **)&authp,
                        (ub4) OCI_HTYPE_SESSION, (size_t) 0, (dvoid **) 0);

  (void) OCIAttrSet((dvoid *) authp, (ub4) OCI_HTYPE_SESSION,
                 (dvoid *) username, (ub4) strlen((char *)username),
                 (ub4) OCI_ATTR_USERNAME, errhp);

  (void) OCIAttrSet((dvoid *) authp, (ub4) OCI_HTYPE_SESSION,
                 (dvoid *) password, (ub4) strlen((char *)password),
                 (ub4) OCI_ATTR_PASSWORD, errhp);

  checkerr(errhp, OCISessionBegin ( svchp,  errhp, authp, OCI_CRED_RDBMS,
                          (ub4) OCI_DEFAULT));

  (void) OCIAttrSet((dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX,
                   (dvoid *) authp, (ub4) 0,
                   (ub4) OCI_ATTR_SESSION, errhp);

  /* Prepare an SQL statement */

  // We begin by allocating a handle for our SQL statement(s)

  checkerr(errhp, OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &stmthp,
           OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0));

  // Once we have the handle, the next step is always to prepare
  // the statement

  checkerr(errhp, OCIStmtPrepare(stmthp, errhp, course_count,
                                (ub4) strlen((char *) course_count),
                                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));
  /* bind the input variable */

  checkerr(errhp, OCIDefineByPos(stmthp, &defnp, errhp, 1, (dvoid *) &ccount,
                   (sword) sizeof(sword), SQLT_INT, (dvoid *) 0, (ub2 *)0,
                   (ub2 *)0, OCI_DEFAULT));

  /* execute and fetch */

  // Be sure and check the return status and account for any possibilities
  // like no tuples returned, a single tuple returned, or multiple tuples
  // returned.

  if (status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
               (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
  {
    if (status == OCI_NO_DATA) {
      fprintf(stderr, "No data on select count(*) from course\n");
    } else
    {
      checkerr(errhp, status);
      cleanup();
      return OCI_ERROR;
    }
  }
  printf("Course count: %d\n", ccount);

  // The next example will execute an SQL statement with more than one
  // projected attributes, but still with only a single tuple returned.

  // We begin by preparing the statement.  Note that we can reuse the
  // statement handle.

  checkerr(errhp, OCIStmtPrepare(stmthp, errhp, course_ten,
                                (ub4) strlen((char *) course_ten),
                                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));

  /* bind the input variables */

  checkerr(errhp, OCIDefineByPos(stmthp, &defnp1, errhp, 1, (dvoid *) &cno,
                   (sword) sizeof(sword), SQLT_INT, (dvoid *) 0, (ub2 *)0,
                   (ub2 *)0, OCI_DEFAULT));

  checkerr(errhp, OCIDefineByPos(stmthp, &defnp2, errhp, 2, (dvoid *) descr_buf,
                   (sword) sizeof(descr_buf), SQLT_STR, (dvoid *) 0, (ub2 *)0,
                   (ub2 *)0, OCI_DEFAULT));

  checkerr(errhp, OCIDefineByPos(stmthp, &defnp3, errhp, 3, (dvoid *) &ccost,
                   (sword) sizeof(sword), SQLT_INT, (dvoid *) 0, (ub2 *)0,
                   (ub2 *)0, OCI_DEFAULT));

  if (status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
               (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
  {
    if (status == OCI_NO_DATA) {
      fprintf(stderr, "No data on select from course\n");
    } else
    {
      checkerr(errhp, status);
      cleanup();
      return OCI_ERROR;
    }
  }
  printf("Course number, descr, cost: %d | %s | %d\n", cno, descr_buf, ccost);

  // Final example demonstrates fetching multiple tuples as the result
  // of an SQL query

  // We begin by preparing the statement.  Note that we can reuse the
  // statement handle.

  checkerr(errhp, OCIStmtPrepare(stmthp, errhp, course_low,
                                (ub4) strlen((char *) course_low),
                                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));

  /* bind the input variables */

  checkerr(errhp, OCIDefineByPos(stmthp, &defnp1, errhp, 1, (dvoid *) &cno,
                   (sword) sizeof(sword), SQLT_INT, (dvoid *) 0, (ub2 *)0,
                   (ub2 *)0, OCI_DEFAULT));

  checkerr(errhp, OCIDefineByPos(stmthp, &defnp2, errhp, 2, (dvoid *) descr_buf,
                   (sword) sizeof(descr_buf), SQLT_STR, (dvoid *) 0, (ub2 *)0,
                   (ub2 *)0, OCI_DEFAULT));

  checkerr(errhp, OCIDefineByPos(stmthp, &defnp3, errhp, 3, (dvoid *) &ccost,
                   (sword) sizeof(sword), SQLT_INT, (dvoid *) 0, (ub2 *)0,
                   (ub2 *)0, OCI_DEFAULT));

  // Note on the stmt execution that we set the fourth parameter to zero
  // to defer any fetch until the loop below.

  if (status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 0, (ub4) 0,
               (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
  {
    if (status == OCI_NO_DATA) {
      fprintf(stderr, "No data on select from course\n");
    } else
    {
      checkerr(errhp, status);
      cleanup();
      return OCI_ERROR;
    }
  }

  while ((status = OCIStmtFetch2(stmthp, errhp, (ub4) 1, (ub2) OCI_FETCH_NEXT,
				 (sb4) 0, OCI_DEFAULT)) == OCI_SUCCESS) {
    printf("Course number, descr, cost: %d | %s | %d\n", 
	   cno, descr_buf, ccost);
  }
  if (status == OCI_NO_DATA) {
    fprintf(stderr, "No data on select from course\n");
  } else
    {
      checkerr(errhp, status);
      cleanup();
      return OCI_ERROR;
    }
}


void checkerr(errhp, status)
OCIError *errhp;
sword status;
{
  text errbuf[512];
  sb4 errcode = 0;

  switch (status)
  {
  case OCI_SUCCESS:
    break;
  case OCI_SUCCESS_WITH_INFO:
    (void) printf("Error - OCI_SUCCESS_WITH_INFO\n");
    break;
  case OCI_NEED_DATA:
    (void) printf("Error - OCI_NEED_DATA\n");
    break;
  case OCI_NO_DATA:
    (void) printf("Error - OCI_NODATA\n");
    break;
  case OCI_ERROR:
    (void) OCIErrorGet((dvoid *)errhp, (ub4) 1, (text *) NULL, &errcode,
                        errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
    (void) printf("Error - %.*s\n", 512, errbuf);
    break;
  case OCI_INVALID_HANDLE:
    (void) printf("Error - OCI_INVALID_HANDLE\n");
    break;
  case OCI_STILL_EXECUTING:
    (void) printf("Error - OCI_STILL_EXECUTE\n");
    break;
  case OCI_CONTINUE:
    (void) printf("Error - OCI_CONTINUE\n");
    break;
  default:
    break;
  }
}


/*
 *  Exit program with an exit code.
 */
void cleanup()
{
  if (envhp)
    (void) OCIHandleFree((dvoid *) envhp, OCI_HTYPE_ENV);
  return;
}


void myfflush()
{
  eb1 buf[50];

  fgets((char *) buf, 50, stdin);
}


#if 0
#ifdef RCSID
static char *RCSid =
   "$Header: cdemo81.c 14-jul-99.13:02:37 mjaeger Exp $ ";
#endif /* RCSID */

/* Copyright (c) 1996, 1999, Oracle Corporation.  All rights reserved.
*/

/*

   NAME
     cdemo81.c - Basic OCI V8 functionality

   DESCRIPTION

 *  An example program which adds new employee
 *  records to the personnel data base.  Checking
 *  is done to insure the integrity of the data base.
 *  The employee numbers are automatically selected using
 *  the current maximum employee number as the start.
 *
 *  The program queries the user for data as follows:
 *
 *  Enter employee name:
 *  Enter employee job:
 *  Enter employee salary:
 *  Enter employee dept:
 *
 *  The program terminates if return key (CR) is entered
 *  when the employee name is requested.
 *
 *  If the record is successfully inserted, the following
 *  is printed:
 *
 *  "ename" added to department "dname" as employee # "empno"

   Demonstrates creating a connection, a session and executing some SQL.
   Also shows the usage of allocating memory for application use which has the
   life time of the handle.

   MODIFIED   (MM/DD/YY)
   mjaeger     07/14/99 - bug 808870: OCCS: convert tabs, no long lines
   dchatter    10/14/98 - add the usage of xtrmemsz and usrmempp
   azhao       06/23/97 - Use OCIBindByPos, OCIBindByName; clean up
   echen       12/17/96 - OCI beautification
   dchatter    07/18/96 - delete spurious header files
   dchatter    07/15/96 - hda is a ub4 array to prevent bus error
   mgianata    06/17/96 - change ociisc() to OCISessionBegin()
   aroy        04/26/96 - change OCITransCommitt -> OCITransCommit
   slari       04/24/96 - use OCITransCommitt
   aroy        02/21/96 - fix bug in get descriptor handle call
   lchidamb    02/20/96 - cdemo81.c converted for v8 OCI
   lchidamb    02/20/96 - Creation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oci.h>

static text *username = (text *) "SCOTT";
static text *password = (text *) "TIGER";

/* Define SQL statements to be used in program. */
static text *insert = (text *)"INSERT INTO emp(empno, ename, job, sal, deptno)\
  VALUES (:empno, :ename, :job, :sal, :deptno)";
static text *seldept = (text *)"SELECT dname FROM dept WHERE deptno = :1";
static text *maxemp = (text *)"SELECT NVL(MAX(empno), 0) FROM emp";
static text *selemp = (text *)"SELECT ename, job FROM emp";

static OCIEnv *envhp;
static OCIError *errhp;

static void checkerr(/*_ OCIError *errhp, sword status _*/);
static void cleanup(/*_ void _*/);
static void myfflush(/*_ void _*/);
int main(/*_ int argc, char *argv[] _*/);

static sword status;

int main(argc, argv)
int argc;
char *argv[];
{

  sword    empno, sal, deptno;
  sword    len, len2, rv, dsize, dsize2;
  sb4      enamelen = 10;
  sb4      joblen = 9;
  sb4      deptlen = 14;
  sb2      sal_ind, job_ind;
  sb2      db_type, db2_type;
  sb1      name_buf[20], name2_buf[20];
  text     *cp, *ename, *job, *dept;

  sb2      ind[2];                                              /* indicator */
  ub2      alen[2];                                         /* actual length */
  ub2      rlen[2];                                         /* return length */

  OCIDescribe  *dschndl1 = (OCIDescribe *) 0,
               *dschndl2 = (OCIDescribe *) 0,
               *dschndl3 = (OCIDescribe *) 0;

  OCISession *authp = (OCISession *) 0;
  OCIServer *srvhp;
  OCISvcCtx *svchp;
  OCIStmt   *inserthp,
            *stmthp,
            *stmthp1;
  OCIDefine *defnp = (OCIDefine *) 0;

  OCIBind  *bnd1p = (OCIBind *) 0;             /* the first bind handle */
  OCIBind  *bnd2p = (OCIBind *) 0;             /* the second bind handle */
  OCIBind  *bnd3p = (OCIBind *) 0;             /* the third bind handle */
  OCIBind  *bnd4p = (OCIBind *) 0;             /* the fourth bind handle */
  OCIBind  *bnd5p = (OCIBind *) 0;             /* the fifth bind handle */
  OCIBind  *bnd6p = (OCIBind *) 0;             /* the sixth bind handle */

  (void) OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,
                       (dvoid * (*)(dvoid *, size_t)) 0,
                       (dvoid * (*)(dvoid *, dvoid *, size_t))0,
                       (void (*)(dvoid *, dvoid *)) 0 );

  (void) OCIEnvInit( (OCIEnv **) &envhp, OCI_DEFAULT, (size_t) 0,
                     (dvoid **) 0 );

  (void) OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, OCI_HTYPE_ERROR,
                   (size_t) 0, (dvoid **) 0);

  /* server contexts */
  (void) OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, OCI_HTYPE_SERVER,
                   (size_t) 0, (dvoid **) 0);

  (void) OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, OCI_HTYPE_SVCCTX,
                   (size_t) 0, (dvoid **) 0);

  (void) OCIServerAttach( srvhp, errhp, (text *)"", strlen(""), 0);

  /* set attribute server context in the service context */
  (void) OCIAttrSet( (dvoid *) svchp, OCI_HTYPE_SVCCTX, (dvoid *)srvhp,
                     (ub4) 0, OCI_ATTR_SERVER, (OCIError *) errhp);

  (void) OCIHandleAlloc((dvoid *) envhp, (dvoid **)&authp,
                        (ub4) OCI_HTYPE_SESSION, (size_t) 0, (dvoid **) 0);

  (void) OCIAttrSet((dvoid *) authp, (ub4) OCI_HTYPE_SESSION,
                 (dvoid *) username, (ub4) strlen((char *)username),
                 (ub4) OCI_ATTR_USERNAME, errhp);

  (void) OCIAttrSet((dvoid *) authp, (ub4) OCI_HTYPE_SESSION,
                 (dvoid *) password, (ub4) strlen((char *)password),
                 (ub4) OCI_ATTR_PASSWORD, errhp);

  checkerr(errhp, OCISessionBegin ( svchp,  errhp, authp, OCI_CRED_RDBMS,
                          (ub4) OCI_DEFAULT));

  (void) OCIAttrSet((dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX,
                   (dvoid *) authp, (ub4) 0,
                   (ub4) OCI_ATTR_SESSION, errhp);

  checkerr(errhp, OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &stmthp,
           OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0));

  checkerr(errhp, OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &stmthp1,
           OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0));

  /* Retrieve the current maximum employee number. */
  checkerr(errhp, OCIStmtPrepare(stmthp, errhp, maxemp,
                                (ub4) strlen((char *) maxemp),
                                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));

  /* bind the input variable */
  checkerr(errhp, OCIDefineByPos(stmthp, &defnp, errhp, 1, (dvoid *) &empno,
                   (sword) sizeof(sword), SQLT_INT, (dvoid *) 0, (ub2 *)0,
                   (ub2 *)0, OCI_DEFAULT));

  /* execute and fetch */
  if (status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
               (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
  {
    if (status == OCI_NO_DATA)
      empno = 10;
    else
    {
      checkerr(errhp, status);
      cleanup();
      return OCI_ERROR;
    }
  }


  /*
   * When we bind the insert statement we also need to allocate the storage
   * of the employee name and the job description.
   * Since the lifetime of these buffers are the same as the statement, we
   * will allocate it at the time when the statement handle is allocated; this
   * will get freed when the statement disappears and there is less
   * fragmentation.
   *
   * sizes required are enamelen+2 and joblen+2 to allow for \n and \0
   *
   */


  checkerr(errhp, OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &inserthp,
           OCI_HTYPE_STMT, (size_t) enamelen + 2 + joblen + 2,
           (dvoid **) &ename));
  job   = (text *) (ename+enamelen+2);


  checkerr(errhp, OCIStmtPrepare(stmthp, errhp, insert,
                                (ub4) strlen((char *) insert),
                                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));

  checkerr(errhp, OCIStmtPrepare(stmthp1, errhp, seldept,
                                (ub4) strlen((char *) seldept),
                                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));


  /*  Bind the placeholders in the INSERT statement. */
  if ((status = OCIBindByName(stmthp, &bnd1p, errhp, (text *) ":ENAME",
             -1, (dvoid *) ename,
             enamelen+1, SQLT_STR, (dvoid *) 0,
             (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) ||
      (status = OCIBindByName(stmthp, &bnd2p, errhp, (text *) ":JOB",
             -1, (dvoid *) job,
             joblen+1, SQLT_STR, (dvoid *) &job_ind,
             (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) ||
      (status = OCIBindByName(stmthp, &bnd3p, errhp, (text *) ":SAL",
             -1, (dvoid *) &sal,
             (sword) sizeof(sal), SQLT_INT, (dvoid *) &sal_ind,
             (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) ||
      (status = OCIBindByName(stmthp, &bnd4p, errhp, (text *) ":DEPTNO",
             -1, (dvoid *) &deptno,
             (sword) sizeof(deptno), SQLT_INT, (dvoid *) 0,
             (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) ||
      (status = OCIBindByName(stmthp, &bnd5p, errhp, (text *) ":EMPNO",
             -1, (dvoid *) &empno,
             (sword) sizeof(empno), SQLT_INT, (dvoid *) 0,
             (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)))
  {
    checkerr(errhp, status);
    cleanup();
    return OCI_ERROR;
  }

  /*  Bind the placeholder in the "seldept" statement. */
  if (status = OCIBindByPos(stmthp1, &bnd6p, errhp, 1,
           (dvoid *) &deptno, (sword) sizeof(deptno),SQLT_INT,
           (dvoid *) 0, (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT))
  {
    checkerr(errhp, status);
    cleanup();
    return OCI_ERROR;
  }

  /*  Allocate the dept buffer now that you have length. */
  /* the deptlen should eventually get from dschndl3.    */
  deptlen = 14;
  dept = (text *) malloc((size_t) deptlen + 1);

  /*  Define the output variable for the select-list. */
  if (status = OCIDefineByPos(stmthp1, &defnp, errhp, 1,
                             (dvoid *) dept, deptlen+1, SQLT_STR,
                             (dvoid *) 0, (ub2 *) 0, (ub2 *) 0, OCI_DEFAULT))
  {
    checkerr(errhp, status);
    cleanup();
    return OCI_ERROR;
  }

  for (;;)
  {
    /* Prompt for employee name.  Break on no name. */
    printf("\nEnter employee name (or CR to EXIT): ");
    fgets((char *) ename, (int) enamelen+1, stdin);
    cp = (text *) strchr((char *) ename, '\n');
    if (cp == ename)
    {
      printf("Exiting... ");
      cleanup();
      return OCI_SUCCESS;
    }
    if (cp)
      *cp = '\0';
    else
    {
      printf("Employee name may be truncated.\n");
      myfflush();
    }
    /*  Prompt for the employee's job and salary. */
    printf("Enter employee job: ");
    job_ind = 0;
    fgets((char *) job, (int) joblen + 1, stdin);
    cp = (text *) strchr((char *) job, '\n');
    if (cp == job)
    {
      job_ind = -1;            /* make it NULL in table */
      printf("Job is NULL.\n");/* using indicator variable */
    }
    else if (cp == 0)
    {
      printf("Job description may be truncated.\n");
      myfflush();
    }
    else
      *cp = '\0';

    printf("Enter employee salary: ");
    scanf("%d", &sal);
    myfflush();
    sal_ind = (sal <= 0) ? -2 : 0;  /* set indicator variable */

    /*
     *  Prompt for the employee's department number, and verify
     *  that the entered department number is valid
     *  by executing and fetching.
     */
    do
    {
      printf("Enter employee dept: ");
      scanf("%d", &deptno);
      myfflush();
      if ((status = OCIStmtExecute(svchp, stmthp1, errhp, (ub4) 1, (ub4) 0,
               (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
          && (status != OCI_NO_DATA))
      {
        checkerr(errhp, status);
        cleanup();
        return OCI_ERROR;
      }
      if (status == OCI_NO_DATA)
        printf("The dept you entered doesn't exist.\n");
      } while (status == OCI_NO_DATA);

      /*
       *  Increment empno by 10, and execute the INSERT
       *  statement. If the return code is 1 (duplicate
       *  value in index), then generate the next
       *  employee number.
       */
      empno += 10;
      if ((status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
               (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
               && status != 1)
      {
        checkerr(errhp, status);
        cleanup();
        return OCI_ERROR;
      }
      while (status == 1)
      {
        empno += 10;
        if ((status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
               (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
                && status != 1)
        {
          checkerr(errhp, status);
          cleanup();
          return OCI_ERROR;
        }
      }  /* end for (;;) */

      /* Commit the change. */
      if (status = OCITransCommit(svchp, errhp, 0))
      {
        checkerr(errhp, status);
        cleanup();
        return OCI_ERROR;
      }
      printf("\n\n%s added to the %s department as employee number %d\n",
                 ename, dept, empno);
  }
}


void checkerr(errhp, status)
OCIError *errhp;
sword status;
{
  text errbuf[512];
  sb4 errcode = 0;

  switch (status)
  {
  case OCI_SUCCESS:
    break;
  case OCI_SUCCESS_WITH_INFO:
    (void) printf("Error - OCI_SUCCESS_WITH_INFO\n");
    break;
  case OCI_NEED_DATA:
    (void) printf("Error - OCI_NEED_DATA\n");
    break;
  case OCI_NO_DATA:
    (void) printf("Error - OCI_NODATA\n");
    break;
  case OCI_ERROR:
    (void) OCIErrorGet((dvoid *)errhp, (ub4) 1, (text *) NULL, &errcode,
                        errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
    (void) printf("Error - %.*s\n", 512, errbuf);
    break;
  case OCI_INVALID_HANDLE:
    (void) printf("Error - OCI_INVALID_HANDLE\n");
    break;
  case OCI_STILL_EXECUTING:
    (void) printf("Error - OCI_STILL_EXECUTE\n");
    break;
  case OCI_CONTINUE:
    (void) printf("Error - OCI_CONTINUE\n");
    break;
  default:
    break;
  }
}


/*
 *  Exit program with an exit code.
 */
void cleanup()
{
  if (envhp)
    (void) OCIHandleFree((dvoid *) envhp, OCI_HTYPE_ENV);
  return;
}


void myfflush()
{
  eb1 buf[50];

  fgets((char *) buf, 50, stdin);
}


/* end of file cdemo81.c */

#endif
