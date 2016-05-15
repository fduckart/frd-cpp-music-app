#include <iostream>
#include <string>
#include <assert.h>
#include "repository.h"
#include "record.h"
#include <limits>

const int TEST_RUNS = 1;
// const int TEST_RUNS = numeric_limits<int>::max();

// Prototypes.
void testConstructor();
void testNextArtistId();
void testNextRecordId();
void testGetArtists();
void testGetRecords();
void testFindRecord();
void testAddRecord();
void testCreatePart1();
void testCreatePart2();
void testUpdatePart1();
void testUpdatePart2();
void testUpdatePart3();

// Main driver.
int main()
{
    cout << "Start Repository tests...\n";

    for (int i = 0; i < TEST_RUNS; i++) {
        testConstructor();
        testNextArtistId();
        testNextRecordId();
        testGetArtists();
        testGetRecords();
        testFindRecord();
        testAddRecord();

        testCreatePart1();
        testCreatePart2();

        testUpdatePart1();
        testUpdatePart2();
        testUpdatePart3();
    }

    cout << "End   Repository test.\n";

    return 0;
}

void testAddRecord()
{
    cout << "Running testAddRecord...";

    Repository rep("music://dirName/records.xml");
    int recordCount = rep.getRecordCount();
    int artistCount = rep.getArtistCount();

    // Check if the artist we are going
    // to add is already in the system.
    // If so, the artist count won't go up.
    Artist fa = rep.findArtist("Brian Eno");

    Artist a1(11, "Brian Eno");

    Record r1("1", a1);
    r1.setGenre("Rock");
    r1.setTitle("Another Green World");
    Track r1t1(1, "Sky Saw");
    r1.addTrack(r1t1);
    Track r1t2(2, "Over Fire Island");
    r1.addTrack(r1t2);
    Track r1t3(3, "St. Elmo's Fire");
    r1.addTrack(r1t3);

    // Add the record to the repository.
    rep.addRecord(r1);

    // Should have one more record.
    assert( (recordCount + 1) == rep.getRecordCount() );
    assert( rep.getArtistCount() != 0 );

    // Check the artist count, if possible.
    if (fa.getArtistId() == 0 && fa.getName() == "null")
      assert( (artistCount + 1) == rep.getArtistCount() );

    // See if we can retrieve that same record.
    Record rf1 = rep.findRecord("1");
    assert( rf1.getRecordId() == r1.getRecordId() );
    assert( rf1.getTitle() == r1.getTitle() );

    // See if the artist is the same.
    Artist * af1 = rf1.getArtist();
    assert( af1->getArtistId() == a1.getArtistId() );
    assert( af1->getName() == a1.getName() );

    rep.deleteRecord(r1.getRecordId());
    assert( recordCount == rep.getRecordCount() );

    cout << "OK\n";
}

void testGetArtists()
{
    cout << "Running testGetArtistCount...";

    Repository rep("music://dirName/records.xml");
    int artistCount1 = rep.getArtistCount();
    int artistCount2 = rep.getArtists().size();
    assert( artistCount1 == artistCount2 );

    cout << "OK\n";
}

void testGetRecords()
{
    cout << "Running testGetRecords...";

    Repository rep("music://dirName/records.xml");
    int recordCount1 = rep.getRecordCount();
    int recordCount2 = rep.getRecords().size();
    assert( recordCount1 == recordCount2 );

    cout << "OK\n";
}

void testFindRecord()
{
    cout << "Running testFindRecord...";

    Repository rep("music://dirName/records.xml");

    // Repository should be empty, so a
    // find should retrieve the 'empty' Record.
    Record r = rep.findRecord("1");
    assert( r.getRecordId() == "null" );
    assert( r.getTitle() == "" );

    cout << "OK\n";
}

void testConstructor()
{
    cout << "Running testConstructor...";

    Repository rep("music://dirName/records.xml");

    cout << "OK\n";
}

void testNextArtistId()
{
    cout << "Running testNextArtistId...";

    Repository rep("music://dirName/records.xml");

    int artistId1 = rep.nextArtistId();
    assert( artistId1 != 0 );

    artistId1++;
    int artistId2 = rep.nextArtistId();
    assert( artistId2 == artistId1 );

    cout << "OK\n";
}

void testNextRecordId()
{
    cout << "Running testNextRecordId...";

    Repository rep("music://dirName/records.xml");

    string recordId1 = rep.nextRecordId();
    string recordId2 = rep.nextRecordId();
    assert( recordId1 != recordId2 );

    cout << "OK\n";
}

// This is the first part of a test to create and then
// retrieve a record after shutting down repository
// and restarting it in the second part.  The record
// file should be on the file system after part 1.
void testCreatePart1()
{
    cout << "Running testCreatePart1...";

    Repository rep("music://dirName/records.xml");
    int recordCount = rep.getRecordCount();

    // Make sure the test record doesn't exist.
    Record fr = rep.findRecord("1");
    assert(fr.getRecordId() == "null");

    Artist a(1, "Louis Armstrong");
    Record r("1", a);
    r.setTitle("Hot Fives And Sevens");
    r.setGenre("Jazz");

    // Count shouldn't have moved yet.
    assert(recordCount == rep.getRecordCount());

    // Add the record; count should go up one.
    rep.addRecord(r);
    assert((recordCount + 1) == rep.getRecordCount());

    cout << "OK\n";
}

// Second part of the record create test.  This test
// needs to verify the existence of the file created in
// part one of the test.  This test will cleanup file.
void testCreatePart2()
{
    cout << "Running testCreatePart2...";

    Repository rep("music://dirName/records.xml");
    int recordCount = rep.getRecordCount();

    // Make sure the test record exists.
    Record fr = rep.findRecord("1");
    assert(fr.getRecordId() == "1");
    assert(fr.getTitle() == "Hot Fives And Sevens");
    assert(fr.getGenre() == "Jazz");

    // Add the record; count should go down one.
    rep.deleteRecord(fr.getRecordId());
    assert((recordCount - 1) == rep.getRecordCount());

    cout << "OK\n";
}

// This is the first part of a test to update and then
// modify a record after shutting down repository
// and restarting it in the second part.  The record
// file should be on the file system after part 1.
void testUpdatePart1()
{
    cout << "Running testUpdatePart1...";

    Repository rep("music://dirName/records.xml");
    int recordCount = rep.getRecordCount();

    // Make sure the test record doesn't exist.
    Record fr = rep.findRecord("11");
    assert(fr.getRecordId() == "null");

    Artist a(2, "Herbie Hancock");
    Record r("11", a);
    r.setTitle("Head Hunter");
    r.setGenre("Dixie Land Jazz");

    Track t(1, "Chameleon");
    r.addTrack(t);

    // Count shouldn't have moved yet.
    assert(recordCount == rep.getRecordCount());

    // Add the record; count should go up one.
    rep.addRecord(r);
    assert((recordCount + 1) == rep.getRecordCount());

    cout << "OK\n";
}

// Second part of the record update test.  This test
// needs to verify the existence of the file created in
// part one of the test.  It will then modify the record
// and save the update.  Part 3 verify the change.
void testUpdatePart2()
{
    cout << "Running testUpdatePart2...";

    Repository rep("music://dirName/records.xml");
    int recordCount = rep.getRecordCount();

    // Make sure the test record exists.
    Record fr = rep.findRecord("11");
    assert(fr.getRecordId() == "11");
    assert(fr.getTitle() == "Head Hunter");
    assert(fr.getGenre() == "Dixie Land Jazz");
    assert(fr.getTrackCount() == 1);
    assert(fr.getTrack(1).getTitle() == "Chameleon");

    // Okay, make some changes.
    fr.setTitle("Head Hunters");
    fr.setGenre("Jazz Fusion");
    Track t2(2, "Watermelon Man");
    fr.addTrack(t2);

    // Record count should still be the same.
    rep.updateRecord(fr);
    assert(recordCount == rep.getRecordCount());

    cout << "OK\n";
}

// Third part of the record update test.  This test
// needs to verify the existence of the file created in
// part one of the test, and verify the change made in
// part 2.  It will then delete the record.
void testUpdatePart3()
{
    cout << "Running testUpdatePart2...";

    Repository rep("music://dirName/records.xml");
    int recordCount = rep.getRecordCount();

    // Make sure the test record exists.
    Record fr = rep.findRecord("11");
    assert(fr.getRecordId() == "11");
    assert(fr.getTitle() == "Head Hunters");
    assert(fr.getGenre() == "Jazz Fusion");
    assert(fr.getTrackCount() == 2);
    assert(fr.getTrack(1).getTitle() == "Chameleon");
    assert(fr.getTrack(2).getTitle() == "Watermelon Man");

    // Add the record; count should go down one.
    rep.deleteRecord(fr.getRecordId());
    assert((recordCount - 1) == rep.getRecordCount());

    cout << "OK\n";
}
