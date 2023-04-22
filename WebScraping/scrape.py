from bs4 import BeautifulSoup
import requests

url = "https://catalog.ufl.edu/UGRD/courses/computer_and_information_science_and_engineering/"

response = requests.get(url)

page = BeautifulSoup(response.content, 'html.parser')

# print(courseCatalog.prettify())

courseTable = []
row = []

courses = page.find_all("div", {"class": "courseblock courseblocktoggle"})

for course in courses:
    # Get Title
    courseTitle = course.find("p", {"class": "courseblocktitle noindent"})
    courseTitle = courseTitle.find("strong")
    courseTitle = courseTitle.text.strip()
    row.append(courseTitle)

    # Get Credits
    courseCredits = course.find("span", {"class": "credits"}).text.strip()
    row.append(courseCredits)


    # Get Pre Reqs
    extraBlocks = course.find_all("p", {"class": "courseblockextra noindent"})
    hasPreReq = False

    for block in extraBlocks:
        if(block.find("strong")):
            # this is the block that has the preReqs
            # pre reqs may be , text, or hlink
            hasPreReq = True
            preReqList = []

            # Get all Link Titles, push them to the list
            # for link in block.find_all("a", {"class": "bubblelink code"}):
            #     if link:
            #         preReqList.append(link.text)

            for item in block:
                if(item.name == "a"):
                    name = item.text[0:3]
                    number = item.text[4:]
                    id = name + " " + number
                    preReqList.append(id)
                else:
                    preReqList.append(item)
            preReqList = preReqList[2:]

    


    print(f"Class: {courseTitle}")
    print(f"Credits: {courseCredits}")
    print(f"preReq: {preReqList}")
    # if(hasPreReq):
    #     print(f"PreRequisites: {preReq}\n")
    # else:
    #     print("NO Pre-Reqs")