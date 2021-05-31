import System.IO
import System.Exit
import Data.Char (isSpace)
import Data.List (elemIndex)
import Data.List (elemIndices)
import Data.Map (Map)
import qualified Data.Map as Map

main = do
       handle <- openFile "file.html" ReadMode
       contents <- hGetContents handle
       let lineContents = lines contents
           tagContents = map (++">") (map trim (wordsWhen (=='>') (trim contents)))
           tagList = map (takeWhile (/=' ')) $ getTags (tagContents)  --Ignore attributes
           noBrHrTagList = filter (\x -> x/= "hr" ) $ filter (\x -> x/= "br" ) tagList
       checkMissingBracket lineContents
       checkTagName tagList
       checkHtml tagList
       checkHeadBody tagList
       checkClosingTag tagList
       checkProperNesting noBrHrTagList
       checkCorrectNesting tagList
       putStrLn "HTML file is valid."
       hClose handle


-- Split raw file when sees char p
wordsWhen :: (Char -> Bool) -> String -> [String]
wordsWhen p s = case dropWhile p s of 
                     "" -> []
                     s' -> w : wordsWhen p s''
                           where (w, s'') = break p s'


-- delete the space in the front or end of a string
trim :: String -> String
trim = f . f
    where f = reverse . dropWhile isSpace

getTags :: [String] -> [String]
getTags xs = map getTag $ map deleteContent xs

getTag :: String -> String
getTag [] = []
getTag ('<':xs) = getTag $ takeWhile (/='>') xs
getTag ('>':xs) = getTag $ dropWhile (/='<') xs
getTag (x:xs) = x : getTag xs 

deleteContent :: String -> String
deleteContent [] = []
deleteContent (x:xs) = if x == '<' then x:xs else deleteContent xs

checkMissingBracket lineContents = do 
                                   if (noMissingBracket lineContents)
                                   then return ()  
                                   else do putStrLn "Missing bracket!"
                                           exitFailure

noMissingBracket :: [String] -> Bool
noMissingBracket xs = countLeftBracket xs == countRightBracket xs

countLeftBracket :: [String] -> Int
countLeftBracket [] = 0
countLeftBracket [x] = length $ filter (=='<') $ x
countLeftBracket (x:xs) = countLeftBracket [x] + (countLeftBracket xs)

countRightBracket :: [String] -> Int
countRightBracket [] = 0
countRightBracket [x] = length $ filter (=='>') $ x
countRightBracket (x:xs) = countRightBracket [x]  + (countRightBracket xs)

checkTagName tagList = do 
                       let validTagList = ["html","head","body","title","h1","h2","h3","p","ul",
                                            "li","a","div","br","hr","/html","/head","/body","/title",
                                            "/h1","/h2","/h3","/p","/ul","/li","/a","/div"]
                       if (isValidTag tagList validTagList)
                       then return ()  
                       else do putStrLn "Invalid tag name!"
                               exitFailure

isValidTag :: [String] -> [String] -> Bool
isValidTag [] zs = True
isValidTag [x] zs = if x `elem` zs then True else False
isValidTag (x:xs) zs = (if x `elem` zs then True else False) && (isValidTag xs zs)

checkHtml tagList = do 
                    if (head tagList == "html" && last tagList == "/html")
                    then return ()  
                    else do putStrLn "No <html>and</html> tags around the entire document."
                            exitFailure

checkHeadBody tagList = do
                        if (isSingleHeadBody tagList)
                        then return ()  
                        else do putStrLn "No single <head>...</head> section followed by a single <body>...</body> section in that order."
                                exitFailure

isSingleHeadBody xs = xs!!1 == "head" && xs!!(length xs -2) == "/body" && rightPosition xs && notMultiple xs
rightPosition xs = position "/head" xs +1 == position "body" xs
notMultiple xs = notMultipleHead xs && notMultipleBody xs
notMultipleHead xs = length (elemIndices "head" xs) == 1 && length (elemIndices "/head" xs) == 1 
notMultipleBody xs = length (elemIndices "body" xs) == 1 && length (elemIndices "/body" xs) == 1

position :: Eq a => a -> [a] -> Int
position i xs =
    case i `elemIndex` xs of
        Just n -> n
        Nothing -> -1

checkClosingTag tagList = do 
                          let n = countTag tagList
                          if n == 0 then return ()
                          else  if n > 0  then do putStrLn "Missing corresponding closing tag!"
                                                  exitFailure
                                else do putStrLn "Missing corresponding open tag!"
                                        exitFailure
                        
countTag :: [String] -> Int
countTag xs = countOpenTag xs - countClosingTag xs

countOpenTag :: [String] -> Int
countOpenTag [] = 0
countOpenTag [x]
        | x !! 0 /= '/' && x /= "hr" && x /= "br"  = 1
        | otherwise                                = 0
countOpenTag (x:xs) = countOpenTag [x] + countOpenTag xs

countClosingTag :: [String] -> Int
countClosingTag [] = 0
countClosingTag [x]
        | x !! 0 == '/'  = 1
        | otherwise      = 0
countClosingTag (x:xs) = countClosingTag [x] + countClosingTag xs

checkProperNesting tagList = do 
                             if balanced tagList
                             then return ()
                             else do putStrLn "Not nested properly."
                                     exitFailure

matchingTags :: Map String String
matchingTags = Map.fromList [
    ("html", "/html"), ("title", "/title"), ("h3", "/h3"), ("li", "/li"),
    ("head", "/head"), ("h1", "/h1"), ("p", "/p"), ("a", "/a"),
    ("body", "/body"), ("h2", "/h2"), ("ul", "/ul"), ("div", "/div")
  ]

isOpening :: String -> Bool
isOpening x = maybe False (const True) $ Map.lookup x matchingTags

type Stack a = [a]

balanced :: [String] -> Bool
balanced = balanced' []

balanced' :: Stack String -> [String] -> Bool
balanced' [] []     = True
balanced' _  []     = False
balanced' [] (x:xs) = balanced' [x] xs
balanced' (o:os) (x:xs)
  | isOpening x = balanced' (x:o:os) xs
  | otherwise   = case Map.lookup o matchingTags of
      Nothing -> False
      Just closing -> if closing == x
        then balanced' os xs
        else False

checkCorrectNesting tagList = do
                              if (isCorrectNesting tagList)
                              then return ()
                              else do putStrLn "(<p>, <div> or <title>) Not nested correctly."
                                      exitFailure

isCorrectNesting xs = correctNestingDiv xs && correctNestingP xs && correctNestingTitle xs

correctNestingDiv xs = do
                       let pIndices = elemIndices "p" xs 
                           closingPIndices = elemIndices "/p" xs
                           divIndices = elemIndices "div" xs
                           pTagIndexTuple = zip pIndices closingPIndices
                       if divIndices == [] then True else and (map (\x -> checkNestingOnce x pTagIndexTuple) divIndices)
                       
correctNestingP xs = do
                     let pIndices = elemIndices "p" xs 
                         closingPIndices = elemIndices "/p" xs
                         pTagIndexTuple = zip pIndices closingPIndices
                     if pIndices == [] then True else and (map (\x -> checkNestingOnce x pTagIndexTuple) pIndices)

correctNestingTitle xs = do
                         let bodyIndices = elemIndices "body" xs 
                             closingBodyIndices = elemIndices "/body" xs
                             titleIndices = elemIndices "title" xs
                             bodyTagIndexTuple = zip bodyIndices closingBodyIndices
                         if titleIndices == [] then True else and (map (\x -> checkNestingOnce x bodyTagIndexTuple) titleIndices)

checkNestingOnce :: Int -> [(Int,Int)] -> Bool
checkNestingOnce _ [] = True
checkNestingOnce a [x] | (a < snd(x)) && (fst(x) < a)  = False
                       | otherwise                     = True
checkNestingOnce a (x:xs) = checkNestingOnce a [x] && checkNestingOnce a xs