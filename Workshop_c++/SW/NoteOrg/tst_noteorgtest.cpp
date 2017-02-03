#include <string>
#include <QtTest>
#include <QFile>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

class Note
{
public:
    virtual std::string title() = 0;
    virtual std::string content() = 0;
    virtual void addParent(Note* parent) = 0;
    virtual std::vector<Note*> find(const std::string &title) = 0;
    virtual void remove(Note* ptr) = 0;
    virtual void printTitle(int tabs = 0) = 0;
};

class AbstractNote : public Note
{
public:
    AbstractNote(const std::string &title) : m_title(title) {}

    std::string title() { return m_title; }

    Note* parent() { return m_parent; }
    void addParent(Note* parent) override { m_parent = parent; }

    std::vector<Note*> find(const std::string &title) {
        if(title == AbstractNote::title())
            return {this};
        return {};
    }

    void printTitle(int tabs = 0) override {
        std::cout << AbstractNote::title() << std::endl;
    }

private:
    std::string m_title;

    Note* m_parent = nullptr;
};

class GroupNote : public AbstractNote
{
public:
    GroupNote(const std::string &title) : AbstractNote(title) {}

    void addNote(std::unique_ptr<Note> note) {
        note->addParent(this);
        m_notes.push_back(std::move(note));
    }

    void remove(Note* ptr){
        int index = 0;
        for(int i=0; i<m_notes.size(); ++i)
        {
            if(m_notes[i].get() == ptr)
            {
                index = i;
                break;
            }
            m_notes.erase(m_notes.begin() + index);
        }

    }

    // Note interface
    std::string content() override {
        std::string output;
        for(auto &note : m_notes)
            output += note->content() + "\n";
        return output;
    }

    std::vector<Note*> find(const std::string &title) {
        std::vector<Note*> result;
        for(auto &note : m_notes)
        {
            auto tempRes = note->find(title);
            result.insert(result.end(), tempRes.begin(), tempRes.end());
        }
        return result;
    }

    void printTitle(int tabs = 0) override {
        AbstractNote::printTitle();
        for(auto &note : m_notes)
        {
            for(int i=0; i<tabs; ++i)
                std::cout << "    ";
            std::cout << "|- ";
            note->printTitle(tabs+1);
        }
    }

private:
    std::vector<std::unique_ptr<Note>> m_notes;
};

class FileNote : public AbstractNote
{
public:
    FileNote(const std::string &title, const std::string &filename) : AbstractNote(title), m_filename(filename) {}

    // Note interface
    std::string content() override {
        QFile f(m_filename.c_str());
        if(f.exists())
        {
            f.open(QFile::ReadOnly);
            return f.readAll().toStdString();
        }
        return "error";
    }

    void remove(Note* ptr) override {
        parent()->remove(this);
    }

private:
    std::string m_filename;
};

class TextNote : public AbstractNote
{
public:
    TextNote(const std::string &title, const std::string &text) : AbstractNote(title), m_text(text) {}

    // Note interface
    std::string content() override { return m_text; }

    void remove(Note* ptr) override {
        parent()->remove(this);
    }

private:
    std::string m_text;
};

class NoteOrgTest : public QObject
{
    Q_OBJECT

public:
    NoteOrgTest();

private Q_SLOTS:
    void test_text_note_title();
    void test_file_note_title();

    void test_text_note_content();
    void test_file_note_content();

    void test_group_note();

    void test_remove();
};

NoteOrgTest::NoteOrgTest()
{
}

void NoteOrgTest::test_text_note_title()
{
    TextNote tn("title", "content");
    QVERIFY2(tn.title() == "title", "Title failure");
}

void NoteOrgTest::test_file_note_title()
{
    FileNote fn("title", "filename");
    QVERIFY2(fn.title() == "title", "Title failure");
}

void NoteOrgTest::test_text_note_content()
{
    TextNote tn("title", "content");
    QVERIFY2(tn.content() == "content", "Content failure");
}

void NoteOrgTest::test_file_note_content()
{
    QFile tf("testfile");
    tf.open(QFile::WriteOnly);
    tf.write("hei");
    tf.close();

    FileNote fn("title", "testfile");
    QVERIFY2(fn.content() == "hei", "Content failure");
}

void NoteOrgTest::test_group_note()
{
    GroupNote root("root");

    auto shopping = std::make_unique<GroupNote>("shopping");
    auto groceries = std::make_unique<GroupNote>("groceries");
    auto todo = std::make_unique<GroupNote>("todo");

    auto monday = std::make_unique<TextNote>("monday", "apples");
    auto tuesday = std::make_unique<TextNote>("tuesday", "oranges");

    auto todolist = std::make_unique<FileNote>("todolist", "todo.txt");

    todo->addNote(std::move(todolist));

    groceries->addNote(std::move(tuesday));
    groceries->addNote(std::move(monday));

    shopping->addNote(std::move(groceries));

    root.addNote(std::move(shopping));
    root.addNote(std::move(todo));

    //root.printTitle();

    QVERIFY2(root.find("not").size() == 0, "find error");

    Note* note = root.find("todo").at(0);
    QVERIFY2(note->title() == "todo", "find error");

    root.remove(note);
    root.printTitle();
}

void NoteOrgTest::test_remove()
{

}

QTEST_APPLESS_MAIN(NoteOrgTest)

#include "tst_noteorgtest.moc"
