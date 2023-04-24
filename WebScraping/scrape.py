from bs4 import BeautifulSoup
import requests
import pandas as pd

url = "https://catalog.ufl.edu/UGRD/courses/computer_and_information_science_and_engineering/"

response = requests.get(url)

page = BeautifulSoup(response.content, 'html.parser')

courseTable = []

courses = page.find_all("div", {"class": "courseblock courseblocktoggle"})

for course in courses:
    # Get Title
    courseTitle = course.find("p", {"class": "courseblocktitle noindent"})
    courseTitle = courseTitle.find("strong")
    courseTitle = courseTitle.text.strip()

    courseID = courseTitle
    courseID = courseID[:8]

    courseName = courseTitle
    courseName = courseName[9:-9]
    courseName = courseName.strip()


    # Get Credits
    courseCredits = course.find("span", {"class": "credits"}).text.strip()
    courseCredits = courseCredits[:-8]



    # Get Pre Reqs
    extraBlocks = course.find_all("p", {"class": "courseblockextra noindent"})
    hasPreReq = False
    preReqList = ""
    preReqDataFrame

    for block in extraBlocks:
        if(block.find("strong") and block.find("strong").text == "Prerequisite:"):
            # this is the block that has the preReqs
            # pre reqs may be , text, or hlink
            hasPreReq = True

            # Get all Link Titles, push them to the list
            # for link in block.find_all("a", {"class": "bubblelink code"}):
            #     if link:
            #         preReqList.append(link.text)
            for item in block:
                if(item.name == "a"):
                    name = item.text[0:3]
                    number = item.text[4:]
                    id = name + " " + number
                    # pre
                    preReqList += id + ","
                else:
                    # preReqList.append(item)
                    preReqList += item.text + ","
            
            preReqList = preReqList[18:]
            
            
    
    courseTable.append([courseID, courseName, courseCredits, preReqList])


df = pd.DataFrame( courseTable, columns= ["ID","Name", "Credits", "PreRequisites"])
df.to_csv("OuputTest1.csv")



# print(f"Class: {courseTitle}")
# print(f"Credits: {courseCredits}")
# print(f"preReq: {preReqList}")
# if(hasPreReq):
#     print(f"PreRequisites: {preReq}\n")
# else:
#     print("NO Pre-Reqs")