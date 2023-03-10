from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("search", views.search, name="search"),
    path("newfile", views.newfile, name="newfile"),
    path("savepage", views.savepage, name="savepage"),
    path("editpage", views.editpage, name="editpage"),
    path("randompage", views.randompage, name="randompage"),
    path("<str:title>", views.entry, name="ENTRY")
]
